# -*- coding: cp1252 -*-
######################################################################
#
# Royal Render Plugin script for Blender 
# Authors, based on:    Felix Bucella, Patrik Gleich
# Authors:              Friedrich Wessel (Callisto FX GmbH)
# Authors, updated by:  Holger Schoenberger (Binary Alchemy)
#
# rrInstall_Copy:     \*\scripts\startup\
# 
######################################################################

bl_info = {
    "name": "Royal Render Submitter",
    "author": "Holger Schoenberger",
    "version": (1, 0),
    "blender": (2, 75, 0),
    "description": "Submit scene to Royal Render",
    "category": "Render",
    }

import bpy
import os
import tempfile
import sys
import subprocess

class RoyalRender_Submitter(bpy.types.Panel):
    """Creates an XML and start the RR Submitter"""
    bl_label = "RoyalRender Submitter"
    bl_idname = "OBJECT_PT_RRSubmitter"
    bl_space_type = 'PROPERTIES'
    bl_region_type = 'WINDOW'
    bl_context = "render"

    def draw(self, context):
        layout = self.layout

        # We submit the current scene. In the future we can implement multi scene submission as RR layers
        scn = context.scene
        img_type = scn.render.image_settings.file_format

        renderOut = bpy.path.abspath(scn.render.filepath)
        
        layout.label("Submit Scene Values: ")
        split = layout.split(percentage=0.05)
        split.separator()
        col = split.column()
        row = col.row()
        row.label("StartFrame: " + str(scn.frame_start))
        row.label("EndFrame: " + str(scn.frame_end))
        col.label("ImageType: " + img_type)
        col.label("ImageName: " + os.path.basename(renderOut))
        col.label("RenderDir: " + os.path.dirname(renderOut))
        
        layout.operator("royalrender.submitscene")
        
class OBJECT_OT_SubmitScene(bpy.types.Operator):
    bl_idname = "royalrender.submitscene"
    bl_label = "Submit Scene"
    
    def get_RR_Root(self):
        if 'RR_ROOT' in os.environ: 
            return os.environ['RR_ROOT']

        if sys.platform.lower().startswith('win'):
            HCPath = "%RRLocationWin%"
        elif sys.platform.lower() == "darwin":
            HCPath = "%RRLocationMac%"
        else:
            HCPath = "%RRLocationLx%"
        if not HCPath.startswith("%"):
            return HCPath

        self.report({'ERROR'},
                    "No RR_ROOT environment variable set!"
                    "\n Please execute     rrWorkstationInstaller and restart.")

    @staticmethod
    def writeNodeStr(fileID, name, text):
        text = text.replace("&", "&amp;")
        text = text.replace("<", "&lt;")
        text = text.replace(">", "&gt;")
        text = text.replace("\"", "&quot;")
        text = text.replace("'", "&apos;")
        fileID.write("    <{0}>  {1}   </{0}>\n".format(name, text))

    @staticmethod
    def writeNodeInt(fileID, name, number):
        fileID.write("    <{0}>  {1}   </{0}>\n".format(name, number))

    @staticmethod
    def writeNodeBool(fileID, name, value):
        fileID.write("    <{0}>   {1}   </{0}>\n".format(name, int(value)))
    
    def rrSubmit(self):
        self.report({'DEBUG'}, "Platform: {0}".format(sys.platform))

        fileID = tempfile.NamedTemporaryFile(mode='w', prefix="rrSubmitBlender_", suffix=".xml", delete=False)
        TempFileName = fileID.name
        self.report({'DEBUG'}, "Create temp Submission File: {0}".format(TempFileName))

        fileID.write("<RR_Job_File syntax_version=\"6.0\">\n")
        fileID.write("<DeleteXML>1</DeleteXML>\n")

        scn = bpy.context.scene

        img_type = scn.render.image_settings.file_format
        rendertarget = img_type.replace("OPEN_", "")
        if rendertarget == "FFMPEG":
            ImageSingleOutputFile = True
            rendertarget = scn.render.ffmpeg.format
        elif rendertarget == "JPEG2000":
            ImageSingleOutputFile = False
            rendertarget = scn.render.image_settings.jpeg2k_codec
        else:
            ImageSingleOutputFile = False
            rendertarget = rendertarget.replace("TARGA_RAW", "RAWTGA")
            rendertarget = rendertarget.replace("TARGA", "TGA")

        renderOut = bpy.path.abspath(scn.render.filepath)

        try:
            hash_idx = renderOut.rindex('#')
            renderPadding = hash_idx - next(i for i in range(hash_idx, 0, -1) if renderOut[i] != '#')
        except ValueError:
            hash_idx = -1
            renderPadding = 4

        extension = ""

        if scn.render.use_file_extension:
            if ImageSingleOutputFile:
                extension = "." + rendertarget.lower()

                if extension.startswith(".avi"):
                    extension = ".avi"
                    rendertarget = rendertarget.replace("_", "")

                extension = extension.replace(".tiff", ".tif")
                extension = extension.replace(".jpeg", ".jpg")

                extension = extension.replace(".quicktime", ".mov")
                extension = extension.replace(".flash", ".flv")
                extension = extension.replace(".mpeg1", ".mpg")
                extension = extension.replace(".mpeg2", ".dvd")
                extension = extension.replace(".mpeg4", ".mp4")

                # if the video extension is not part of the output filename,
                # blender will add the frame range
                if renderOut.lower().endswith(extension.lower()):
                    renderOut = renderOut[:-len(extension)]
                else:
                    if hash_idx == -1:
                        renderOut = "{0}{1:0{3}d}-{2:0{3}d}".format(renderOut,
                                                                    scn.frame_start, scn.frame_end,
                                                                    renderPadding)
                    else:
                        prefix, suffix = renderOut.rsplit("#" * renderPadding, 1)
                        renderOut = "{0}{1:0{3}d}-{2:0{3}d}{4}".format(prefix,
                                                                       scn.frame_start, scn.frame_end,
                                                                       renderPadding,
                                                                       suffix)
            else:
                extension = scn.render.file_extension

        app_ver = bpy.app.version
        writeNodeStr = self.writeNodeStr
        writeNodeInt = self.writeNodeInt
        writeNodeBool = self.writeNodeBool

        fileID.write("<Job>\n")
        writeNodeStr(fileID, "Software", "Blender")
        writeNodeStr(fileID, "Version",  "{0}.{1}".format(app_ver[0], app_ver[1]))
        #writeNodeStr(fileID, "Layer", scn.render.layers[0].name)
        writeNodeStr(fileID, "SceneName", bpy.data.filepath)
        writeNodeBool(fileID, "IsActive", True)
        writeNodeBool(fileID, "ImageSingleOutputFile", ImageSingleOutputFile)
        writeNodeInt(fileID, "SeqStart", scn.frame_start)
        writeNodeInt(fileID, "SeqEnd", scn.frame_end)
        writeNodeInt(fileID, "SeqStep", scn.frame_step)
        writeNodeStr(fileID, "ImageDir", os.path.dirname(renderOut))
        writeNodeStr(fileID, "ImageFilename", os.path.basename(renderOut))
        writeNodeInt(fileID, "ImageFramePadding", renderPadding)
        writeNodeStr(fileID, "ImageExtension", extension)
        if 'MULTILAYER' in rendertarget:
            rendertarget = "MULTILAYER"
        else:
            writeNodeStr(fileID, "Layer", scn.render.layers[0].name)
        if rendertarget in ("TGA", "RAWTGA", "JPEG", "IRIS", "IRIZ", "AVIRAW",
                            "AVIJPEG", "PNG", "BMP", "HDR", "TIFF", "EXR", "MULTILAYER",
                            "MPEG", "FRAMESERVER", "CINEON", "DPX", "DDS", "JP2"):
            writeNodeStr(fileID, "CustomFrameFormat", rendertarget)
        fileID.write("</Job>\n")
        fileID.write("</RR_Job_File>\n")
        fileID.close()

        RR_ROOT = self.get_RR_Root()
        if RR_ROOT is None:
            return False

        self.report({'DEBUG'}, "Found RR_Root:{0}".format(RR_ROOT))

        if sys.platform.lower().startswith("win"):
            submitCMDs = ('{0}\\win__rrSubmitter.bat'.format(RR_ROOT),
                          TempFileName)
        elif sys.platform.lower() == "darwin":
            submitCMDs = ('{0}/bin/mac64/rrSubmitter.app/Contents/MacOS/rrSubmitter'.format(RR_ROOT), TempFileName)
        else:
            submitCMDs = ('{0}/lx__rrSubmitter.sh'.format(RR_ROOT), TempFileName)

        try:
            subprocess.run(submitCMDs, check=True)
        except FileNotFoundError:
            self.report({'ERROR'}, "rrSubmitter not found\n({0})".format(submitCMDs[0]))
            return False
        except subprocess.CalledProcessError:
            self.report({'ERROR'}, "Error while executing rrSubmitter")
            return False

        return True
        
    def execute(self, context):
        self.report({'INFO'}, "Saving mainFile...")
        bpy.ops.wm.save_mainfile()
        if self.rrSubmit():
            self.report({'INFO'}, "Submit Launch Successfull")
        else:
            self.report({'ERROR'}, "Submit Scene Failed")

        return{'FINISHED'}
 
    
    

def register():
    bpy.utils.register_class(RoyalRender_Submitter)
    bpy.utils.register_class(OBJECT_OT_SubmitScene)


def unregister():
    bpy.utils.unregister_class(RoyalRender_Submitter)
    bpy.utils.unregister_class(OBJECT_OT_SubmitScene)
    
if __name__ == "__main__":
    bpy.utils.register_module(__name__)
