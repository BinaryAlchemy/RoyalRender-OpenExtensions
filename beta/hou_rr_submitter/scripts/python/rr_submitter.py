import os
import hou
import sys
import random
import logging
import subprocess

#import rr_submitter as rr

##############################################
# Logging functions                          #
##############################################

# logging config
logging_format = "%(name)s :: %(levelname)s :: %(message)s"
logging.basicConfig(level=logging.DEBUG, format=logging_format) # set level to logging.INFO to disable DEBUG logs
logger = logging.getLogger(__name__)

def writeInfo(msg):
    """
    Writes info to stdout using logger
    """
    logger.info(msg)

def writeError(msg, details=None):
    """
    Writes error to stdout using logger and prompts UI windows with the same message

    Additional information can be pased to details argument which user will be able to expand in the UI
    """
    # include details in logger output
    msg_stderr = msg
    if details:
        msg_stderr += " :: {}".format(details)

    logger.error(msg_stderr)
    hou.ui.displayMessage(text="Royal Render encountered an error:", severity=hou.severityType.Error, help=msg, title="Royal Render", details=details, details_label="Show more...")


##############################################
# Job class                                  #
##############################################


class rrJob(object):
         
    def __init__(self):
        self.clear()
    
    def clear(self):
        self.version = ""
        self.software = ""
        self.renderer = ""
        self.rendererVersion = ""
        self.RequiredLicenses = ""
        self.sceneName = ""
        self.sceneDatabaseDir = ""
        self.seqStart = 0
        self.seqEnd = 100
        self.seqStep = 1
        self.seqFileOffset = 0
        self.seqFrameSet = ""
        self.imageWidth = 99
        self.imageHeight = 99
        self.imageDir = ""
        self.imageFileName = ""
        self.imageFramePadding = 4
        self.imageExtension = ""
        self.imagePreNumberLetter = ""
        self.imageSingleOutput = False
        self.imageStereoR = ""
        self.imageStereoL = ""
        self.sceneOS = ""
        self.camera = ""
        self.layer = ""
        self.channel = ""
        self.maxChannels = 0
        self.channelFileName = []
        self.channelExtension = []
        self.isActive = False
        self.sendAppBit = ""
        self.preID = ""
        self.waitForPreID  = ""
        self.CustomA  = ""
        self.CustomB  = ""
        self.CustomC  = ""
        self.LocalTexturesFile  = ""

    # from infix.se (Filip Solomonsson)
    def indent(self, elem, level=0):
        i = "\n" + level * ' '
        if len(elem):
            if not elem.text or not elem.text.strip():
                elem.text = i + " "
            for e in elem:
                self.indent(e, level + 1)
                if not e.tail or not e.tail.strip():
                    e.tail = i + " "
            if not e.tail or not e.tail.strip():
                e.tail = i
        else:
            if level and (not elem.tail or not elem.tail.strip()):
                elem.tail = i
        return True

    def subE(self, r, e, text):
        sub = SubElement(r, e)
        if (type(text) == unicode ):
            sub.text = text.encode('utf8')
        else:
            sub.text = str(text).decode("utf8")
        return sub
    
    def writeToXMLstart(self, submitOptions ):
        rootElement = Element("rrJob_submitFile")
        rootElement.attrib["syntax_version"] = "6.0"
        self.subE(rootElement, "DeleteXML", "1")
        self.subE(rootElement, "SubmitterParameter", submitOptions)
        # YOU CAN ADD OTHER NOT SCENE-INFORMATION PARAMETERS USING THIS FORMAT:
        # self.subE(jobElement,"SubmitterParameter","PARAMETERNAME=" + PARAMETERVALUE_AS_STRING)
        return rootElement

    def writeToXMLJob(self, rootElement):
        jobElement = self.subE(rootElement, "Job", "")
        self.subE(jobElement, "rrSubmitterPluginVersion", "%rrVersion%-s")
        self.subE(jobElement, "Software", self.software)
        self.subE(jobElement, "Renderer", self.renderer)
        self.subE(jobElement, "rendererVersion", self.rendererVersion)
        self.subE(jobElement, "RequiredLicenses", self.RequiredLicenses)
        self.subE(jobElement, "Version", self.version)
        self.subE(jobElement, "SceneName", self.sceneName)
        self.subE(jobElement, "SceneDatabaseDir", self.sceneDatabaseDir)
        self.subE(jobElement, "IsActive", self.isActive)
        self.subE(jobElement, "SeqStart", self.seqStart)
        self.subE(jobElement, "SeqEnd", self.seqEnd)
        self.subE(jobElement, "SeqStep", self.seqStep)
        self.subE(jobElement, "SeqFileOffset", self.seqFileOffset)
        self.subE(jobElement, "SeqFrameSet", self.seqFrameSet)
        self.subE(jobElement, "ImageWidth", int(self.imageWidth))
        self.subE(jobElement, "ImageHeight", int(self.imageHeight))
        self.subE(jobElement, "ImageDir", self.imageDir)
        self.subE(jobElement, "ImageFilename", self.imageFileName)
        self.subE(jobElement, "ImageFramePadding", self.imageFramePadding)
        self.subE(jobElement, "ImageExtension", self.imageExtension)
        self.subE(jobElement, "ImageSingleOutput", self.imageSingleOutput)
        self.subE(jobElement, "ImagePreNumberLetter", self.imagePreNumberLetter)
        self.subE(jobElement, "ImageStereoR", self.imageStereoR)
        self.subE(jobElement, "ImageStereoL", self.imageStereoL)
        self.subE(jobElement, "SceneOS", self.sceneOS)
        self.subE(jobElement, "Camera", self.camera)
        self.subE(jobElement, "Layer", self.layer)
        self.subE(jobElement, "Channel", self.channel)
        self.subE(jobElement, "SendAppBit", self.sendAppBit)
        self.subE(jobElement, "PreID", self.preID)
        self.subE(jobElement, "WaitForPreID", self.waitForPreID)
        self.subE(jobElement, "CustomA", self.CustomA)
        self.subE(jobElement, "CustomB", self.CustomB)
        self.subE(jobElement, "CustomC", self.CustomC)
        self.subE(jobElement, "LocalTexturesFile", self.LocalTexturesFile)
        for c in range(0,self.maxChannels):
           self.subE(jobElement,"ChannelFilename",self.channelFileName[c])
           self.subE(jobElement,"ChannelExtension",self.channelExtension[c])
        return True

    def writeToXMLEnd(self, f,rootElement):
        xml = ElementTree(rootElement)
        self.indent(xml.getroot())

        if not f == None:
            xml.write(f)
            f.close()
        else:
            print("No valid file has been passed to the function")
            try:
                f.close()
            except:
                pass
            return False
        return True


##############################################
# Global Functions                           #
##############################################


def getRR_Root():
    if os.environ.has_key('RR_ROOT'):
        return os.environ['RR_ROOT']
    HCPath="%"
    if ((sys.platform.lower() == "win32") or (sys.platform.lower() == "win64")):
        HCPath="%RRLocationWin%"
    elif (sys.platform.lower() == "darwin"):
        HCPath="%RRLocationMac%"
    else:
        HCPath="%RRLocationLx%"
    if HCPath[0]!="%":
        return HCPath
    writeError("This plugin was not installed via rrWorkstationInstaller!")

def getNewTempFileName():
    random.seed()
    if ((sys.platform.lower() == "win32") or (sys.platform.lower() == "win64")):
        if os.environ.has_key('TEMP'):
            nam=os.environ['TEMP']
        else:
            nam=os.environ['TMP']
        nam+="\\"
    else:
        nam="/tmp/"
    nam+="rrSubmitNuke_"
    nam+=str(random.randrange(1000,10000,1))
    nam+=".xml"
    return nam

def getRRSubmitterPath():
    ''' returns the rrSubmitter filename '''
    rrRoot = getRR_Root()
    if ((sys.platform.lower() == "win32") or (sys.platform.lower() == "win64")):
        rrSubmitter = rrRoot+"\\win__rrSubmitter.bat"
    elif (sys.platform.lower() == "darwin"):
        rrSubmitter = rrRoot+"/bin/mac64/rrStartLocal rrSubmitter "
    else:
        rrSubmitter = rrRoot+"/lx__rrSubmitter.sh\""
    return rrSubmitter

def getRRSubmitterconsolePath():
    ''' returns the rrSubmitter filename '''
    rrRoot = getRR_Root()
    if ((sys.platform.lower() == "win32") or (sys.platform.lower() == "win64")):
        rrSubmitter = rrRoot+"\\bin\\win64\\rrStartLocal rrSubmitterconsole "
    elif (sys.platform.lower() == "darwin"):
        rrSubmitter = rrRoot+"/bin/mac64/rrStartLocal rrSubmitterconsole "
    else:
        rrSubmitter = rrRoot+"/bin/lx64/rrStartLocal rrSubmitterconsole "
    return rrSubmitter

def getOSString():
    if ((sys.platform.lower() == "win32") or (sys.platform.lower() == "win64")):
        return "win"
    elif (sys.platform.lower() == "darwin"):
        return "osx"
    else:
        return "lx"

def submitJobsToRR(jobList,submitOptions, nogui=False):
    tmpFileName = getNewTempFileName()
    tmpFile = open(tmpFileName, "w")
    xmlObj= jobList[0].writeToXMLstart(submitOptions)
    for submitjob in jobList:
        submitjob.writeToXMLJob(xmlObj)
    ret = jobList[0].writeToXMLEnd(tmpFile,xmlObj)
    if ret:
        #writeInfo("Job written to " + tmpFile.name)
        pass
    else:
        writeError("Error - There was a problem writing the job file to " + tmpFile.name)
    commandline=""
    if nogui:
        commandline=getRRSubmitterconsolePath() + "  \"" + tmpFileName + "\"" + ' -Wait'
    else:
        commandline= getRRSubmitterPath()+"  \""+tmpFileName+"\""        
    #writeInfo("Executing "+commandline)
    os.system(commandline)


##############################################
# Houdini Functions                          #
##############################################    


def isRenderable(node):
    """
    Checks if a node is renderable and is not rop network itself
    """
    return isinstance(node, hou.RopNode) and node.type().name() != "ropnet"

def getRopNodesAtPath(root_path):
    """
    Returns child renderable nodes found at specified location

    Returns a list of hou.Node objects
    """
    node = hou.node(root_path)
    if not node:
        print('Node "{}" does not exist'.format(root_path))
        return None

    node_children = node.allSubChildren()
    node_list = []

    # check if node is renderable
    if isRenderable(node):
        node_list.append(node)
        return node_list
    # if not, then looks into its children
    elif len(node_children) > 0:
        for n in node_children:
            if isRenderable(n):
                node_list.append(n)

    if len(node_list) > 0:
        return node_list
    else:
        return None

def getSceneRopNodes():
    """
    If a node is selected, finds all renderable nodes in it, if not, then finds all renderable nodes in the scene
    Returns a list of hou.Node objects
    """
    out_nodes = []

    selection = hou.selectedNodes()

    # if user has selected some nodes
    if bool( selection ):
        for selected in selection:
            found_nodes = getRopNodesAtPath( selected.path() )
            if found_nodes:
                for node in found_nodes:
                    out_nodes.append(node)
            else:
                found_nodes = getRopNodesAtPath("/")
                if found_nodes:
                    for node in found_nodes:
                        out_nodes.append(node)
    # if user did not select anything
    else:
        found_nodes = getRopNodesAtPath("/")
        if found_nodes:
            out_nodes = found_nodes
        else:
            return
    
    return out_nodes

def getSceneWedges():
    """
    Returns a list of wedge nodes in the whole scene
    """
    rops = getRopNodesAtPath("/")
    wedges = []

    for node in rops:
        if node.type().name() == "wedge":
            wedges.append(node)
    
    return wedges

def getSceneTakes():
    """
    Rutrns a dict containing takes information
    """
    takes = {}
    takes["current_take"] = hou.takes.currentTake().name()
    takes["all_takes"] = []

    for take in hou.takes.takes():
        takes["all_takes"].append( take.name() )
    
    return takes

def expandPathParm(parm):
    """
    Returns processed and expanded path from input parameter
    """
    in_path = hou.pwd().path()
    hou.cd(parm.node().path())

    if len(parm.keyframes()) == 0:
        expr = parm.unexpandedString()
    else:
        expr = parm.eval()

    expr = expr.replace("$ACTIVETAKE", "<Channel>")
    expr = expr.replace("${ACTIVETAKE}", "<Channel>")
    expr = expr.replace("$WEDGE", "<Wedge>")
    expr = expr.replace("${WEDGE}", "<Wedge>")
    expr = expr.replace("${AOV}.", "<ValueVar @AOV.>")
    expr = expr.replace("${AOV}/", "<ValueVar @AOV/>")
    expr = expr.replace("${AOV}_", "<ValueVar @AOV_>")
    expr = expr.replace("$AOV.", "<ValueVar @AOV.>")
    expr = expr.replace("$AOV/", "<ValueVar @AOV/>")
    expr = expr.replace("$AOV_", "<ValueVar @AOV_>")
    path = hou.expandString(expr)
    expr = expr.replace("@AOV", "@$AOV")  #$AOV is required for the output setting at render time, but expandString would remove it.
    

    hou.cd(in_path)
    return path

class GenericNode(object):
    """
    Abstract class for storing information about a node, this stores information which is common to all renderable nodes
    More specific nodes should subclass this class and store additional information

    input node parameter is of hou.Node type
    """
    def __init__(self, node):
        self.node_object = node
        self.node_name = node.name()
        self.node_path = node.path()

        self.render_engine = self.getRenderEngine()
        self.render_engine_version = self.getRenderEngineVersion()
    
    def getRenderEngine(self):
        """
        Returns a string specifying render engine, supported nodes must be specified here, otherwise an exception will be raised

        TODO
            * differentiate between normal renders and archive renderers
            * ?mapping list could be stored in a dict to make code more readable
            * ?store it in a global (within module scope) dict to make it re-usable by other classes
        """
        type_name = self.node_object.type().name()

        if type_name.lower() == "redshift_rop":
            return "redshift"
        elif type_name.lower() == "Redshift_Proxy_Output":
            return "redshift_proxy"
        elif type_name.lower() == "arnold":
            return "arnold"
        elif type_name.lower() == "arnold_denoiser":
            return "arnold_denoiser"
        elif type_name.lower() == "ifd":
            return "mantra"
        elif type_name.lower() == "geometry":
            return "geometry"
        elif type_name.lower() == "alembic":
            return "alembic"
        elif type_name.lower() == "fetch":
            return "fetch"
        elif type_name.lower() == "merge":
            return "merge"
        elif type_name.lower() == "wedge":
            return "wedge"
        elif type_name.lower() == "opengl":
            return "opengl"
        else:
            msg = 'Node "{}" of type "{}" is not supported'.format(self.node_object.name(), type_name)
            writeError(msg)
            raise NameError(msg)
    
    def getRenderEngineVersion(self):
        """
        Returns a string specifying render engine version, or Houdini version if renderer is houdini/mantra

        TODO
            * refer user to help via details argument in writeError()
        """
        if self.render_engine.startswith("arnold"):
            try:
                import arnold
                return arnold.AiGetVersionString()
            except ImportError:
                msg = 'Failed to import "arnold" python module, htoa is not available.'
                writeError(msg)
                raise ImportError(msg)

        elif self.render_engine.startswith("redshift"):
            ver = hou.hscript('Redshift_version')[0]
            if not ver.startswith("Unknown"):
                return ver
            else:
                msg = 'Failed to run "Redshift_version" command, redshift is not available.'
                writeError(msg)
                raise ImportError(msg)

        else:
            return hou.applicationVersionString()

class RenderNode(GenericNode):
    """
    Class representing render node
    """
    def __init__(self, node):
        super(RenderNode, self).__init__(node)
        self.parms = RenderParms(self)

class RenderParms(object):
    """
    Class for storing information about parameters from ROP node
    """
    def __init__(self, generic_node):
        self.generic_node_object = generic_node
        self.node_object = generic_node.node_object
        self.cam_path = self.getCameraPath()
        self.cam_stereo = self.isCamStereo()
        self.start, self.end, self.steps = self.getFrameRange()
        self.output_path = self.getOutputPath()
        self.aovs = self.getAOVs()
        self.res = self.getResolution()
        
    def getCameraPath(self):
        """
        Returns string containing path to camera
        """
        renderer = self.generic_node_object.render_engine
        if renderer == "arnold" or renderer == "mantra" or renderer == "opengl":
            return self.node_object.parm("camera").evalAsNode().path()
        elif renderer == "redshift":
            return self.node_object.parm("RS_renderCamera").evalAsNode().path()
        else:
            return None
    
    def isCamStereo(self):
        """
        Returns boolean if camera is stereo, or None if there is no camera

        TODO
            * add paths to cameras? for imageStereoL, imageStereoR options
        """
        if self.cam_path:
            cam_node = hou.node(self.cam_path)
            if cam_node.type().name().lower().startswith("stereo"):
                return True
            else:
                return False
        else:
            return None
    
    def getFrameRange(self):
        """
        Returns a touple of (start, end, steps) frame range in a node
        """
        start = self.node_object.parm("f1").eval()
        end = self.node_object.parm("f2").eval()
        steps = self.node_object.parm("f3").eval()

        return (start, end, steps)
    
    def getOutputPath(self):
        """
        Returns expanded string containing path to the output picture

        TODO
            * make the mapping more readable by storing it in a dict
        """
        renderer = self.generic_node_object.render_engine
        parm = None

        if renderer == "arnold":
            parm = "ar_picture"
        elif renderer == "arnold_denoiser":
            parm = "output"
        elif renderer == "redshift":
            parm = "RS_outputFileNamePrefix"
        elif renderer == "redshift_proxy":
            parm = "RS_archive_file"
        elif renderer == "mantra":
            parm = "vm_picture"
        elif renderer == "geometry":
            parm = "sopoutput"
        elif renderer == "alembic":
            parm = "filename"
        elif renderer == "opengl":
            parm = "picture"
        
        if parm:
            parm_obj = self.node_object.parm(parm)
            path = expandPathParm(parm_obj)
            return path
        else:
            return None
    
    def getAOVs(self):
        """
        Returns a dict of aovs in this form { "name" : "path" }
        """
        renderer = self.generic_node_object.render_engine
        if renderer == "arnold":
            multiparm_name = "ar_aovs"
            parm_aov_enable = "ar_enable_aov{num}"
            parm_aov_name = "ar_aov_label{num}"
            parm_aov_file = "ar_aov_separate_file{num}"
            parm_aov_use_file = "ar_aov_separate{num}"
        elif renderer == "mantra":
            multiparm_name = "vm_numaux"
            parm_aov_enable = "vm_disable_plane{num}" # inverted
            parm_aov_name = "vm_variable_plane{num}"
            parm_aov_file = "vm_filename_plane{num}"
            parm_aov_use_file = "vm_usefile_plane{num}"
        elif renderer == "redshift":
            multiparm_name = "RS_aov"
            parm_aov_enable = "RS_aovEnable_{num}"
            parm_aov_name = "RS_aovSuffix_{num}"
            parm_aov_file = "RS_aovCustomPrefix_{num}"
            parm_aov_use_file = 1
        
        multiparm = self.node_object.parm(multiparm_name)
        aovs_num = multiparm.eval()
        aovs = {}
        child_parms = multiparm.multiParmInstances()
        child_parms = [p.name() for p in child_parms]

        for i in xrange(1, aovs_num + 1):
            aov_enable = self.node_object.parm( parm_aov_enable.format(num = i) ).eval()
            if renderer == "mantra":
                aov_enable = 1 - aov_enable
            
            if aov_enable == 1:
                aov_name = self.node_object.parm( parm_aov_name.format(num = i) ).eval()
                aov_file = expandPathParm( self.node_object.parm( parm_aov_file.format(num = i) ) )
                
                if parm_aov_use_file == 1:
                    aov_use_file = 1
                else:
                    aov_use_file = self.node_object.parm( parm_aov_use_file.format(num = i) ).eval()

                if aov_use_file == 1 and aov_file != "":
                    aovs[aov_name] = aov_file
                else:
                    aovs[aov_name] = self.output_path
        return aovs
    
    def getResolution(self):
        """
        Returns a list containing X and Y output image resolution

        TODO
            * add support for redshift and arnold
        """
        renderer = self.generic_node_object.render_engine
        if renderer == "mantra":
            override_parm = "override_camerares"
            override_res_parms = ["res_overridex", "res_overridey"]
            override_mult_parm = "res_fraction"
            cam_res_parms = ["resx", "resy"]
        
        cam_node = hou.node(self.cam_path)
        cam_res_x = cam_node.parm(cam_res_parms[0]).eval()
        cam_res_y = cam_node.parm(cam_res_parms[1]).eval()

        override = bool( self.node_object.parm(override_parm).eval() )

        if override:
            override_mult = self.node_object.parm(override_mult_parm).eval()
            
            if override_mult == "specific":
                res_x = self.node_object.parm(override_res_parms[0]).eval()
                res_y = self.node_object.parm(override_res_parms[1]).eval()
            else:
                res_x = cam_res_x * float(override_mult)
                res_y = cam_res_y * float(override_mult)
            return [res_x, res_y]
        else:
            return [cam_res_x, cam_res_y]

class WedgeNode(GenericNode):
    """
    Class representing wedge node

    self.wedge_method can be either "channel" or "take"
    """
    def __init__(self, node):
        super(WedgeNode, self).__init__(node)
        self.prefix = self.node_object.parm("prefix").eval()
        self.wedge_method = self.node_object.parm("wedgemethod").evalAsString()
        self.driver_path = self.node_object.parm("driver").evalAsNode().path()

        node_inputs = self.node_object.inputs()
        if len( node_inputs ) == 1:
            self.driver_path = node_inputs[0].path()
        self.driver = RenderNode( hou.node(self.driver_path) )
        self.wedge_parms = self.getWedgeParms()
    
    def getWedgeParms(self):
        """
        Returns a dictionary of wedge parameters in this structure:
        {
            "name 1"  : {
                "start" : 1,
                "end" : 10,
                "steps" : 1
            },
            "name 2" : {
                ...
            },
            ...
        }
        """
        multiparm = self.node_object.parm("wedgeparams")
        wedges_num = multiparm.eval()
        wedges = {}
        child_parms = multiparm.multiParmInstances()
        child_parms = [p.name() for p in child_parms]

        for i in xrange(1, wedges_num + 1):
            wedge_name = self.node_object.parm("name{num}".format(num = i)).eval()
            wedge_start = self.node_object.parm("range{num}x".format(num = i)).eval()
            wedge_end = self.node_object.parm("range{num}y".format(num = i)).eval()
            wedge_steps = self.node_object.parm("steps{num}".format(num = i)).eval()

            wedges[wedge_name] = {
                "start" : wedge_start,
                "end" : wedge_end,
                "steps" : wedge_steps
            }
        
        return wedges

def createGenericJob(node):
    """
    Creates rrJob object and fills in submission information
    
    node argument should be of type Hou.Node
    """
    render_node = RenderNode(node)

    newJob = rrJob()

    newJob.version = hou.applicationVersionString()
    newJob.software = "Houdini"
    newJob.renderer = render_node.render_engine
    newJob.rendererVersion = render_node.render_engine_version
    newJob.sceneName = hou.hipFile.path()
    newJob.sceneOS = getOSString()
    newJob.seqStart = render_node.parms.start
    newJob.seqEnd = render_node.parms.end
    newJob.seqStep = render_node.parms.steps
    newJob.imageWidth = render_node.parms.res[0]
    newJob.imageHeight = render_node.parms.res[1]
    newJob.imageFileName = render_node.parms.output_path
    newJob.camera = render_node.parms.cam_path
    
    # continue
    newJob.layer = ""
    newJob.channel = ""

    return newJob
    
    
def createJobsFromNode_arnold(self, jobList, ropNodes, wedges, takes):          
    #TODO: Missing
    pass
    
    
def createJobsFromNode_arnoldDenoise(self, jobList, ropNodes, wedges, takes):          
    #TODO: Missing
    pass
    
    
def createJobsFromNode_redshift(self, jobList, ropNodes, wedges, takes):          
    #TODO: Missing
    pass
    
    
def createJobsFromNode_redshiftProxy(self, jobList, ropNodes, wedges, takes):          
    createJobsFromNode_redshift(jobList, ropNodes, wedges, takes)
    
    
def createJobsFromNode_mantra(self, jobList, ropNodes, wedges, takes):          
    #TODO: Missing
    pass
    
    
def createJobsFromNode_alembic(self, jobList, ropNodes, wedges, takes):          
    #TODO: Missing
    pass
    
    
def createJobsFromNode_openGL(self, jobList, ropNodes, wedges, takes):          
    newJob= createGenericJob()
    newJob.renderer=  self.generic_node_object.render_engine
    

    
    # self.subE(jobElement, "ImageFilename", self.imageFileName)
    # self.subE(jobElement, "ImageFramePadding", self.imageFramePadding)
    # self.subE(jobElement, "ImageExtension", self.imageExtension)
    # self.subE(jobElement, "ImageSingleOutput", self.imageSingleOutput)
    # self.subE(jobElement, "ImagePreNumberLetter", self.imagePreNumberLetter)
    # self.subE(jobElement, "ImageStereoR", self.imageStereoR)
    # self.subE(jobElement, "ImageStereoL", self.imageStereoL)
    # self.subE(jobElement, "Layer", self.layer)
    # self.subE(jobElement, "Channel", self.channel)
    # for c in range(0,self.maxChannels):
        # self.subE(jobElement,"ChannelFilename",self.channelFileName[c])
        # self.subE(jobElement,"ChannelExtension",self.channelExtension[c])

        
    
    
    newJob.isActive = True
    jobList.append(newJob)        
    
    
    
    
def createJobsFromNode(self, jobList, ropNodes, wedges, takes):  
    renderer = self.generic_node_object.render_engine
    if renderer == "arnold":
        createJobsFromNode_arnold(jobList, ropNodes, wedges, takes)
    elif renderer == "arnold_denoiser":
        createJobsFromNode_arnoldDenoise(jobList, ropNodes, wedges, takes)
    elif renderer == "redshift":
        createJobsFromNode_redshift(jobList, ropNodes, wedges, takes)
    elif renderer == "redshift_proxy":
        createJobsFromNode_redshiftProxy(jobList, ropNodes, wedges, takes)
    elif renderer == "mantra":
        createJobsFromNode_mantra(jobList, ropNodes, wedges, takes)
    elif renderer == "geometry":
        createJobsFromNode_geometry(jobList, ropNodes, wedges, takes)
    elif renderer == "alembic":
        createJobsFromNode_alembic(jobList, ropNodes, wedges, takes)
    elif renderer == "opengl":
        createJobsFromNode_openGL(jobList, ropNodes, wedges, takes)
        
        
        
        
def createJobList(jobList, ropNodes, wedges, takes):
    for node in ropNodes:
        renderNode= RenderNode( node )
        renderNode.createJobsFromNode(jobList, ropNodes, wedges, takes)
        
        
        
def rrSubmit_scripted():
    writeInfo ("rrSubmit %rrVersion%")
    hou.hipFile.save()
    sceneFile = hou.hipFile.name()
    rrRoot = getRR_Root()
    if ((sceneFile==None) or (len(sceneFile)==0)):
        return
    wedges= getSceneWedges()
    takes= getSceneTakes()
    ropNodes= getSceneRopNodes()
    jobList= []
    createJobList(jobList, ropNodes, wedges, takes)
    
    submitOptions=""
    
    submitJobsToRR(jobList,submitOptions,nogui)
        

#rrSubmit_scripted()        
        
