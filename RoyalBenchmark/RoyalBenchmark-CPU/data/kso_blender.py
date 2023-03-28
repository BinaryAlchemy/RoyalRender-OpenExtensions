#  Render script for Blender
#  Last Change: 9.0.04
#  Copyright (c)  Holger Schoenberger - Binary Alchemy
#  Author: Paolo Acampora, Binary Alchemy


from collections import OrderedDict
import datetime
import os
import sys
import time
from pathlib import Path

import bpy
import addon_utils


# Global values used in kso functions
GPU_RENDERERS = ("redshift", "Octane", "Eevee")
CURRENT_RENDERER = ""

AV_FRAME_TIME = 0
LOCAL_FRAME_LOOP = False

RENDER_SCENE = ""
RENDER_LAYER = ""
RENDER_PADDING = 4
RENDER_PATH = ""


# Logging

def flush_log():
    sys.stdout.flush()
    sys.stderr.flush()

def log_message_base(lvl, msg):
    msg_start = datetime.datetime.now().strftime("' %H:%M.%S") + " rrBlend"

    if (lvl):
        print(f"{msg_start} - {str(lvl)}: {str(msg)}")
    else:
        print(f"{msg_start}      : {str(msg)}")

def log_msg(msg):
    log_message_base("", msg)

def log_msg_dbg(msg):
    #log_message_base("DBG", msg)
    pass

def log_msg_wrn(msg):
    log_message_base("WRN", msg)

def log_msg_err(msg):
    log_message_base("ERR", str(msg)+"\n\n")
    log_message_base("ERR", "Error reported, aborting render script")

    bpy.ops.wm.quit_blender()


# Startup Utilities

def enable_gpu_devices(addon_name='cycles'):
    v_major, v_minor, _ = bpy.app.version

    if v_major > 2 or v_minor > 79:
        prefs = bpy.context.preferences
    else:
        prefs = bpy.context.user_preferences

    addon_prefs = prefs.addons[addon_name].preferences

    # Attempt to set GPU device types if available
    for compute_device_type in ('CUDA', 'OPENCL', 'NONE'):
        try:
            addon_prefs.compute_device_type = compute_device_type
            break
        except TypeError:
            log_msg_wrn("Failed to enable gpu")
            return False

    # Enable all CPU and GPU devices
    log_msg(f"GPU set to {addon_prefs.compute_device_type}")

    if v_major > 2:
        addon_prefs.refresh_devices()
        devices = addon_prefs.devices
        for device in devices:
            log_msg(f"\tenabling device {device.name}")
            device.use = True
    else:
        devices = addon_prefs.get_devices(bpy.context)
        for device in devices:
            for dev_entry in device:
                log_msg(f"\tenabling device {dev_entry.name}")
                dev_entry.use = True
    
    return True


def enable_addon(addon_name):
    log_msg_wrn(f"*** Loading {addon_name.title()} addon... ***")
    
    try:
        addon_utils.enable(addon_name)
    except ModuleNotFoundError:
        log_msg_wrn(f"Failed to enable addon: {addon_name}")


# Parsing

class RRArgParser(object):
    """ArgParse replacement, parse the command line arguments and store them internally or as global vars for
    kso command. DON'T SET BLENDER VALUE INSIDE THIS CLASS: the scene might not be there yet."""

    def __init__(self, *args):
        self._debug = False

        self.PyModPath=""

        self.blend_file = ""

        self.seq_start = None
        self.seq_end = None
        self.seq_step = 1
        self.padding = 4

        self.kso_mode = False
        self.kso_port = 7774

        self.render_scene = ""
        self.render_layer = ""

        self.renderer = ""
        self.render_filepath = ""
        self.render_fileext = ""
        self.overwrite_existing = None
        self.bl_placeholder = None

        self.anti_alias_mult = 1.0

        self.res_percent = 100
        self.res_x = None
        self.res_y = None
        self.camera = None

        self.enable_gpu = False
        self.load_redshift = False
        self.render_format=""

        self.error = ""
        self.parse(args)

        self.success = self._is_valid()
    
    def _is_valid(self):
        if self._debug:
            print("seq_start", self.seq_start)
            print("seq_end", self.seq_step)

        if not self.seq_start:
            self.error = "Missing argument: -rStart (Sequence Start)"
            return False
        if not self.seq_end:
            self.error = "Missing argument: -rEnd (Sequence End)"
            return False
        # TODO: frame start, end

        return True

    def parse(self, args):
        args = list(args)

        if not args:
            raise Exception("no arguments given: -rStart START_FRAME -rEnd END_FRAME -avMemUsage AV_MEM_USAGE -avRenderTime AV_RENDER_TIME")

        while args:
            arg = args.pop(0)

            # Trigger Flags: only one argument

            if arg == "-rDebug":
                self._debug = True
                continue

            if arg == "--":
                continue

            if arg == "-rKso":
                self.kso_mode = True
                continue

            if arg == "-rGPU":
                self.enable_gpu = True
                continue

            if arg == "-rLoadRS":
                self.load_redshift = True

            # Keyword/Value Flags

            try:
                value = args.pop(0)
            except IndexError:
                if self._debug:
                    print(f" ArgParser: Stopped parsing, last arg was {value}")
                break

            if value.startswith("-"):
                if self._debug:
                    log_msg_wrn(f"Ignored argument {arg}")

                arg = value

            if self._debug:
                print(f" ArgParser: arg: {arg}, value: {value}")

            if arg == "-S":
                self.render_scene = value
                global RENDER_SCENE
                RENDER_SCENE = self.render_scene

            if arg == "-rOverwrite":
                self.overwrite_existing = bool(value)
            
            if arg == "-rPlaceHolder":
                self.bl_placeholder = bool(value)

            if arg == "-rKSOport":
                self.kso_port = int(value)
            
            if arg == "-rAvFrTime":
                global AV_FRAME_TIME
                AV_FRAME_TIME = int(value)

            if arg == "-rOut":
                self.render_filepath = value
                global RENDER_PATH
                RENDER_PATH = self.render_filepath
                continue

            if arg == "-rStart":
                self.seq_start = int(value)
                continue

            if arg == "-rEnd":
                self.seq_end = int(value)
                continue

            if arg == "-rStep":
                self.seq_step = int(value)
                continue

            if arg == "-rPercent":
                self.res_percent = float(value)
                continue

            if arg == "-rX":
                self.res_x = int(value)
                continue

            if arg == "-rY":
                self.res_y = int(value)
                continue

            if arg == "-rRenderer":
                self.renderer = value
                continue

            if arg == "-rCam":
                self.camera = value
                continue

            if arg == "-rAA":
                try:
                    factor = float(value)
                except ValueError:
                    factor = 1.0
                else:
                    self.anti_alias_mult = factor
                continue

            if arg == "-rBlend":
                self.blend_file = value
            
            if arg == "-rExt":
                self.render_fileext = value
            
            if arg == "-rFormat":
                self.render_format = value
            
            if arg == "-rPad":
                self.padding = int(value)
                global RENDER_PADDING
                RENDER_PADDING = self.padding
            
            if arg == "-rLayer":
                self.render_layer = value
                global RENDER_LAYER
                RENDER_LAYER = self.render_layer
            
            if arg == "-rFormat":
                self.format = value

            if arg == "-rPyModPath":
                self.PyModPath = value


# Errors

class RRArgParseException(Exception):
    pass

class RRFilepathMismatchException(Exception):
    pass


# Setup

FFMPEG_CODECS = {'.avi': 'AVI', '.flv': 'FLASH', '.mkv': 'MKV',
                 '.mpg': 'MPEG1','.dvd': 'MPEG2', '.mp4': 'MPEG4',
                 '.ogv': 'OGG', '.mov': 'QUICKTIME', '.webm': 'WEBM'}


OUT_FORMATS = OrderedDict(
    {'BMP': ['.bmp'], 'IRIS': ['.rgb'], 'PNG': ['.png'], 'JPEG': ['.jpg'], 'JPEG2000': ['.jp2', 'j2c'],
     'TARGA': ['.tga'], 'TARGA_RAW': ['.tga'], 'CINEON': ['.cin'], 'DPX': ['.dpx'],
     'OPEN_EXR': ['.exr'], 'OPEN_EXR_MULTILAYER': ['.exr'], 'HDR': ['.hdr'], 'TIFF': ['.tif'], 'WEBP': ['.webp'],
     'FFMPEG': list(FFMPEG_CODECS.keys()),
     'AVI_JPEG': ['.avi'], 'AVI_RAW': ['.avi']}
)


def open_blend_file(blend_file):
    norm_path = os.path.normcase(blend_file)
    norm_path = os.path.normpath(norm_path)

    bpy.ops.wm.open_mainfile(filepath=norm_path)

    if bpy.data.filepath != norm_path:
        raise RRFilepathMismatchException


def set_frame_range(start, end, step):
    scene = bpy.data.scenes[RENDER_SCENE]

    scene.frame_start = start
    scene.frame_end = end
    scene.frame_step = step


def render_frame_range(start, end, step, movie=False):

    scene = bpy.data.scenes[RENDER_SCENE]
    Path(os.path.dirname(scene.render.filepath)).mkdir(parents=True, exist_ok=True)

    if not (movie or LOCAL_FRAME_LOOP):
        log_msg(f"Rendering Frames: {start} - {end}")
        for fr in range(start, end + 1, step):
            if scene.render.use_overwrite:
                # if blender does not overwrite, creating placeholder files will prevent from rendering
                # not considering the case when blender creates its own placeholders via scene.render.use_placeholder.
                # They would overwrite RR placeholders before the render starts.

                #kso_tcp.writeRenderPlaceholder_nr(RENDER_PATH, fr, RENDER_PADDING, scene.render.file_extension)
                pass
            log_msg(f"Rendering Frame #{fr} ...")
            flush_log()

            scene.frame_start = fr
            scene.frame_end = fr
            bpy.ops.render.render(animation=True, write_still=True, use_viewport=False, scene=RENDER_SCENE, layer=RENDER_LAYER)
    else:
        log_msg(f"Rendering Frames (no frame loop): {start} - {end}")
        set_frame_range(start, end, step)
        flush_log()
        bpy.ops.render.render(animation=True, write_still=True, use_viewport=False, scene=RENDER_SCENE, layer=RENDER_LAYER)


def set_output_path():
    scene = bpy.data.scenes[RENDER_SCENE]
    out_path = RENDER_PATH

    if RENDER_PADDING != 4:
        out_path += '#' * RENDER_PADDING

    scene.render.filepath = out_path


def set_output_format(file_ext, file_format='', scene=None):
    scene = bpy.data.scenes[RENDER_SCENE]

    log_msg(f"Scene file format is set to {scene.render.image_settings.file_format}")

    viable_formats = []
    for k, v in OUT_FORMATS.items():
        if file_ext in v:
            viable_formats.append(k)
    
    out_format = ''
    
    if not viable_formats:
        log_msg_wrn(f"No format found for extention '{file_ext}', using parameter '{file_format}'" )
    elif len(viable_formats) == 1:
        out_format = viable_formats[0]

        if file_format:
            log_msg(f"Only one format for rendering {file_ext} files, ignoring format parameter {file_format}")
            if file_format != out_format:
                log_msg_wrn(f"format parameter {file_format} doesn't match {file_ext} format parameter")
        
        if out_format == scene.render.image_settings.file_format:
            log_msg(f"Output format was already set to: {out_format}")
        else:
            log_msg(f"Changing output format to match argument: {file_ext}")
            scene.render.image_settings.file_format = out_format
    elif file_format:
        try:
            extensions = OUT_FORMATS[file_format]
            if file_ext in extensions:
                out_format = file_format
            else:
                log_msg_wrn(f"File format and extension parameters do not match: {file_format}, {file_ext}")
        except:
            log_msg_wrn(f"File format parameter was not found: {file_format}")
    try:
        if out_format:
            scene.render.image_settings.file_format = out_format
        else:
            if scene.render.image_settings.file_format in viable_formats:
                log_msg(f"More formats for extension {file_ext}, using current format {scene.render.image_settings.file_format}")
            else:
                log_msg(f"Changing output format based on extension's default {viable_formats[0]}. Check '-rFormat' parameter (CustomFrameFormat variable in rrControl/rrSubmitter) to do otherwise.")
                
                log_msg(f"Available formats for {file_ext}:")
                for viable_format in viable_formats:
                    log_msg(f"\t{viable_format}")
                log_msg("")

                scene.render.image_settings.file_format = viable_formats[0]
    except:
        log_msg_wrn(f"File format parameter does not exist, unable to override file format: {out_format}")
            
    if out_format == 'FFMPEG':
        # Set container based on extension
        try:
            out_container = FFMPEG_CODECS[file_ext]
        except:
            log_msg_wrn(f"No {out_format} container found for extension {file_ext}, current container is '{scene.render.ffmpeg.format}'")
        else:
            if scene.render.ffmpeg.format != out_container:
                log_msg(f"Setting ffmpeg format to {out_container}")
                scene.render.ffmpeg.format = out_container
    elif out_format == 'JPEG2000':
        scene.render.image_settings.jpeg2k_codec = 'JP2' if file_ext.lower() == '.jp2' else 'J2K'
        log_msg(f"jpeg2k codec set to", scene.render.image_settings.jpeg2k_codec)

    if out_format == 'FFMPEG' or out_format.startswith('AVI'):
        # Video: single output
        LOCAL_FRAME_LOOP = True
    else:
        out_extension = scene.render.file_extension
        if out_extension != file_ext:
            log_msg_wrn(f"Render file extension '{out_extension}' doesn't match job settings '{file_ext}'")



def set_average_frame_time(frame_time):
    global AV_FRAME_TIME
    AV_FRAME_TIME = frame_time

    global LOCAL_FRAME_LOOP
    if not LOCAL_FRAME_LOOP:
        if AV_FRAME_TIME == 0:
            LOCAL_FRAME_LOOP = CURRENT_RENDERER in GPU_RENDERERS
            return

        if AV_FRAME_TIME < 60:
            LOCAL_FRAME_LOOP = True
            return

        if AV_FRAME_TIME < 140:
            LOCAL_FRAME_LOOP = CURRENT_RENDERER in GPU_RENDERERS


def multiply_antialias_settings(renderer, factor):
    if factor == 1.0:
        return

    scene = bpy.data.scenes[RENDER_SCENE]

    if renderer == 'Cycles':
        previous = scene.cycles.filter_width
        scene.cycles.filter_width *= factor

        log_msg(f"{renderer} Filter Width changed from {previous} to {scene.cycles.filter_width}")
        return

    # Generic setting for eevee

    previous = scene.render.filter_size
    scene.render.filter_size *= factor

    log_msg(f"Generic Filter Size changed from {previous} to {scene.render.filter_size}")


def multiply_render_samples(renderer, factor):
    if factor == 1.0:
        return

    scene = bpy.data.scenes[RENDER_SCENE]

    if renderer == "Eevee":
        previous = scene.eevee.taa_render_samples
        scene.eevee.taa_render_samples = round(factor * scene.eevee.taa_render_samples)
        log_msg(f"{renderer} samples changed from {previous} to {scene.eevee.taa_render_samples}")
    elif renderer == "Cycles":
        previous = scene.cycles.samples
        scene.cycles.samples = round(factor * scene.cycles.samples)
        log_msg(f"{renderer} samples changed from {previous} to {scene.cycles.samples}")
    else:
        log_msg_wrn(f"Samples override not supported for {renderer}")


def ensure_scene_and_layer():
    """Use current scene in case no scene was passed"""
    global RENDER_SCENE

    if RENDER_SCENE and RENDER_SCENE not in bpy.data.scenes:
        log_msg_wrn(f"The scene {RENDER_SCENE} was not found in this file, will default to loaded scene")
        RENDER_SCENE = None

    if not RENDER_SCENE:
        RENDER_SCENE = bpy.context.scene.name
        log_msg_wrn(f"No SceneState argument given, using '{RENDER_SCENE}'")
    
    global RENDER_LAYER

    if RENDER_LAYER and RENDER_LAYER not in bpy.data.scenes[RENDER_SCENE].view_layers:
        log_msg_wrn(f"The layer {RENDER_LAYER} was not found in '{RENDER_SCENE}', will default to loaded layer")
        RENDER_LAYER = None

    if not RENDER_LAYER:
        RENDER_LAYER = bpy.context.view_layer.name
        log_msg_wrn(f"No Layer argument given, using '{RENDER_LAYER}'")


def adjust_resolution(new_res_x, new_res_y):
    render_settings = bpy.data.scenes[RENDER_SCENE].render
    if new_res_x:
        res_x = render_settings.resolution_x
        if res_x == new_res_x:
            log_msg(f"Render width already set to {res_x}, no change necessary")
        else:
            render_settings.resolution_x = new_res_x
    if new_res_y:
        res_y = render_settings.resolution_y
        if res_y == new_res_y:
            log_msg(f"Render height already set to {res_y}, no change necessary")
        else:
            render_settings.resolution_y = new_res_y


####

if __name__ == "__main__":
    log_msg(" Royal Render %rrVersion% blender render plugin ".center(100, "_"))
    log_msg(" Blender started ".center(100, "_"))
    log_msg(" Python version: "+str(sys.version))

    args = RRArgParser(*sys.argv)
    
      
    log_msg(" About to open blend file ".center(100, "_"))
    log_msg(f"Open scene file: {args.blend_file}")

    open_blend_file(args.blend_file)
    log_msg(" blend file opened ".center(100, "_"))

    ensure_scene_and_layer()

    context = bpy.context.scene
    if RENDER_SCENE != "":
        if RENDER_SCENE in bpy.data.scenes:
            context = bpy.data.scenes[ RENDER_SCENE ]    
    renderer_pretty_name = context.render.engine.title()
    renderer_prefix = "Blender_"
    if renderer_pretty_name.startswith(renderer_prefix):
        renderer_pretty_name = renderer_pretty_name[len(renderer_prefix):]
    log_msg("Scene renderer is: "+str(renderer_pretty_name))
    if (args.renderer ==  ""):
        args.renderer= renderer_pretty_name
    CURRENT_RENDERER = args.renderer

    if args.enable_gpu:
        enable_gpu_devices()

        if args.renderer == "Cycles":
            settings = bpy.data.scenes[RENDER_SCENE].cycles
            if settings.device != 'GPU':
                log_msg(f"Switching Cycles render device from '{settings.device}' to 'GPU'")
            settings.device = 'GPU'
    
    if args.load_redshift:
        enable_addon("redshift")

    adjust_resolution(args.res_x, args.res_y)
    multiply_render_samples(args.renderer, args.anti_alias_mult)
    
    set_frame_range(args.seq_start, args.seq_end, args.seq_step)
    set_output_path()
    set_output_format(args.render_fileext, args.render_format)

    if args.overwrite_existing != None:
        bpy.data.scenes[RENDER_SCENE].render.use_overwrite = args.overwrite_existing
    
    if args.bl_placeholder != None:
        bpy.data.scenes[RENDER_SCENE].render.use_placeholder = args.bl_placeholder

    # ensure output dir
    Path(os.path.dirname(RENDER_PATH)).mkdir(parents=True, exist_ok=True)
    flush_log()
    
    try:
        render_frame_range(args.seq_start, args.seq_end, args.seq_step)
    except Exception as e:
        log_msg_err(str(e))
     
    log_msg("Task Frames Rendered, Exiting")
