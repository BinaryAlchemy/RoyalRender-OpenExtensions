
import logging
import os
import shutil
import sys
import tempfile
from datetime import datetime


from .errors import RR_EnvironNotFound, RR_RecursiveCopyError, RR_FolderNotFound

logLevel= logging.INFO
#logLevel= logging.DEBUG

rrLogger=logging.getLogger("rrPy")
ch = logging.StreamHandler()
ch.setLevel(logLevel)
#formatter = logging.Formatter("%(asctime)s %(name)s| %(levelname)s:  %(message)s", "%H:%M:%S")
formatter = logging.Formatter("%(asctime)s | %(levelname)s:  %(message)s", "%H:%M:%S")
ch.setFormatter(formatter)
rrLogger.addHandler(ch)
rrLogger.setLevel(logLevel)

    

def get_logger():
    return logging.getLogger("rrPy")
    
    
def is_64bit():
    import struct
    return (struct.calcsize("P") == 8)
    

def get_rr_bin_folder():
    """Return the path of Royal Render's bin folder. Only works if RR was installed on the machine,
     as it relies on the env var RR_ROOT"""
    #for beta sites that use some RR9 apps, but farm is still RR8
    if ('RR_ROOT9' in os.environ):
        rr_path= os.environ['RR_ROOT9']
    else:
        if not ('RR_ROOT' in os.environ):
            raise RR_EnvironNotFound("env var RR_ROOT required to find module search path,"
                                    " please run rrWorkstationInstaller")
            return ""
        rr_path=os.environ['RR_ROOT']

    #for sites that use some RRv9 apps, but farm is still RRv8
    if (not 'rrIsDebug' in os.environ):
        rr_path = rr_path.replace("_debug", "_release")

    if (os.path.exists(os.path.join(rr_path, "_RR9"))):
        rr_path= os.path.join(rr_path, "_RR9")
        
    bin_path = os.path.join(rr_path, "bin")

    if sys.platform.lower().startswith("win"):
        bin_path = os.path.join(bin_path, "win")
    elif sys.platform.lower() == "darwin":
        bin_path = os.path.join(bin_path, "mac")
    else:
        bin_path = os.path.join(bin_path, "lx")
        
    if is_64bit():
        bin_path += '64'
    
    return bin_path


def rr_sync_copy(src_path, dst_path, errors):
    """Copies src_path to dst_path, skips copy if dst_path exists and is up to date"""
    logger = get_logger()

    src_stat = os.stat(src_path)
    if os.path.isfile(dst_path):
        dst_stat = os.stat(dst_path)
        #modifiedSrc = datetime.fromtimestamp(src_stat.st_mtime)
        #modifiedDst = datetime.fromtimestamp(dst_stat.st_mtime)
        #logger.info("{} {} ".format(modifiedSrc, modifiedDst));
        if (abs(src_stat.st_mtime - dst_stat.st_mtime) <= 1) and (src_stat.st_size == dst_stat.st_size):
            logger.debug("skipping: same size and time: {0}".format(src_path))
            return

    logger.debug("Copying file: {} {}".format(src_path,dst_path))

    try:
        if os.path.isfile(dst_path):
            if os.path.isfile(dst_path+".old"):
                if os.path.isfile(dst_path+".old2"):
                    os.remove(dst_path+".old2") 
                os.rename(dst_path+".old", dst_path+".old2")
            os.rename(dst_path, dst_path+".old")
    except OSError as reason:
        errors.extend(("Rename old",  dst_path, str(reason).replace("\\\\", "\\")))        
    # exceptions are handled in parent function
    shutil.copyfile(src_path, dst_path)
    
    try:
        shutil.copystat(src_path, dst_path)
    except OSError as reason:
        logger.error("ERROR {}".format(reason))
        # special exceptions NOT handled in parent function
        if WindowsError is not None and isinstance(reason, WindowsError):
            # Copying file access times may fail on Windows
            logger.warning("Windows Error on stats update: {0}".format(dst_path))
            pass
        else:
            errors.extend(("stat sync", dst_path, str(reason).replace("\\\\", "\\")))


def rr_sync_tree(src_dir, dst_dir, symlinks=False):
    logger = get_logger()
    dir_content = os.listdir(src_dir)

    ignored_names = ('QtGui', 'Qt5Gui', 'QtXml', 'Qt5Xml', 'Qt5Widgets', 
                     'avcodec', 'avformat', 'avutil', 'cuda', 'swscale',
                     'Half', 'Iex', 'IlmImf', 'IlmThread', 'Imath', 'OpenEXR',
                     'libcurl', 'libpng', 'rrJpeg', 'curl', '7z', 
                     'D3Dcompiler', 'iconengines', 'imageformats',
                     'platforms', 'bearer', 'translations')

    if sys.platform.lower().startswith("win32"):
        contain_names = ('.dll', '.pyd')
    elif sys.platform.lower() == "darwin":
        contain_names = tuple() #QT libs have no extension
    else:
        contain_names = ('.so')

    if not os.path.isdir(dst_dir):
        os.makedirs(dst_dir)

    errors = []

    logger.info("Sync local folder " + dst_dir)
    for name in dir_content:
        if any(s in name for s in ignored_names):
            logger.debug("skipping: filename contains ignore string {0}".format(name))
            continue

        if len(contain_names) > 0 and not any(s in name for s in contain_names):
            logger.debug("skipping: filename does not contain extension {0}".format(name))
            continue

        src_path = os.path.join(src_dir, name)
        dst_path = os.path.join(dst_dir, name)
        try:
            if os.path.isdir(src_path):
                rr_sync_tree(src_path, dst_path, symlinks)
            else:
                # Will raise a SpecialFileError for unsupported file types
                rr_sync_copy(src_path, dst_path, errors)

        # catch the Error from the recursive rrSyncTree so that we can
        # continue with other files
        except RR_RecursiveCopyError as err:
            errors.extend(err.args[0])
            errors.append((src_path, dst_path, str(reason).replace("\\\\", "\\")))
        except EnvironmentError as reason:
            errors.append((src_path, dst_path, str(reason).replace("\\\\", "\\")))

    if errors:
        raise RR_RecursiveCopyError(errors)


def cache_module_locally(module_folder=None, target_folder=None):
    """Copy files required for python script execution to a local temp folder, add temp folder to modules path.

    Module files and their required dependenicy libs are locked while they are in use.
    If launched from the RR network folder, they might prevent updating Royal Render files.
    And there is a constant network connection. There have been cases in which a tiny network disruption caused Windows to fail loading additional functions from a dll
    """
    logger = get_logger()

    if ('RR_PYTHON_FOLDER' in os.environ):
        module_path= os.environ['RR_PYTHON_FOLDER']
        sys.path.append(module_path)
        logger.info("added module path " + module_path)
        return
    if ('RR_PYTHON_LIBS_FOLDER' in os.environ):
        module_path= os.environ['RR_PYTHON_LIBS_FOLDER']
        sys.path.append(module_path)
        logger.info("added module path " + module_path)
        return
    
    if not module_folder:
        module_folder = get_rr_bin_folder()

    if not os.path.isdir(module_folder):
        raise RR_FolderNotFound(module_folder)
        
    logger.info("RR source folder ({})".format(module_folder))
    
    # Get the default temp folder
    tmp_folder = tempfile.gettempdir()
    if module_folder.endswith("64"):
        tmp_folder = os.path.join(tmp_folder, "rrbin64_py")
    else:
        tmp_folder = os.path.join(tmp_folder, "rrbin_py")

    if not sys.platform.lower().startswith("win"):
        tmp_folder = os.path.join(tmp_folder, "lib")
        module_folder = os.path.join(module_folder, "lib")

    if ('RR_PYTHON_CACHE_FOLDER' in os.environ):
        tmp_folder= os.environ['RR_PYTHON_CACHE_FOLDER']
        sys.path.append(tmp_folder)
        logger.info("added module path " + tmp_folder)
        
    if target_folder!=None:
        tmp_folder=target_folder    
    logger.info("RR cache target folder ({})".format(tmp_folder))


    rr_sync_tree(module_folder, tmp_folder)

    module_path = tmp_folder
    if sys.platform.lower() == "darwin":
        py_version = sys.version_info
        module_path = os.path.join(module_path, 'python', "{0}{1}".format(py_version.major, py_version.minor))

    sys.path.append(module_path)
    logger.info("added module path " + module_path)

