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
import random
import sys

class RoyalRender_Submitter(bpy.types.Panel):
    """Creates an XML and start the RR Submitter"""
    bl_label = "RoyalRender Submitter"
    bl_idname = "OBJECT_PT_RRSubmitter"
    bl_space_type = 'PROPERTIES'
    bl_region_type = 'WINDOW'
    bl_context = "render"

    def draw(self, context):
        layout = self.layout
        

        #scn = bpy.data.scenes[0]
        #if bpy.data.scenes.__len__() > 1:
        #    print("Blendfile contains more then 1 scene - I take the first one for settings called: " + scn.name)
        scn = bpy.context.scene
        type = scn.render.image_settings.file_format
        rendertarget = type
        extension = "."+rendertarget.lower()
        
        renderOut = os.path.dirname(bpy.data.filepath) + scn.render.filepath
        renderOut = renderOut.replace("//", "\\")
        
        layout.label("Submit Scene Values: ")
        split = layout.split(percentage=0.05)
        col = split.column()
        col = split.column()
        row = col.row()
        row.label("StartFrame: " + str(scn.frame_start))
        row.label("EndFrame: " + str(scn.frame_end))
        col.label("ImageType: " + type)
        col.label("ImageName: " + os.path.basename(renderOut))
        col.label("RenderDir: " +  os.path.dirname(renderOut))  
        
        layout.operator("royalrender.submitscene")
        
class OBJECT_OT_SubmitScene(bpy.types.Operator):
    bl_idname = "royalrender.submitscene"
    bl_label = "Submit Scene"
    
    def get_RR_Root(self):  
        if 'RR_ROOT' in os.environ: 
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
        print("No RR_ROOT environment variable set!\n Please execute     rrWorkstationInstaller and restart.")

    def writeNodeStr(self,fileID,name,text): 
        text=text.replace("&","&amp;")
        text=text.replace("<","&lt;")
        text=text.replace(">","&gt;")
        text=text.replace("\"","&quot;")
        text=text.replace("'","&apos;")
        fileID.write("    <"+name+">  "+text+"   </"+name+">\n")

    def writeNodeInt(self,fileID,name,number):
        fileID.write("    <"+name+">  "+str(number)+"   </"+name+">\n")

    def writeNodeBool(self, fileID,name,value):
        if value:
            fileID.write("    <"+name+">   1   </"+name+">\n")
        else:
            fileID.write("    <"+name+">   0   </"+name+">\n")
    
    def setNewTempFileName(self):
        random.seed()
        if ((sys.platform.lower() == "win32") or (sys.platform.lower() == "win64")):
            if 'TEMP' in os.environ:
                nam=os.environ['TEMP']
            else: 
                nam=os.environ['TMP']
                nam+="\\"
        else:
            nam="/tmp/"
        nam+="rrSubmitBlender_"
        nam+=str(random.randrange(1000,10000,1))
        nam+=".xml"
        return nam
    
    def rrSubmit(self):
        print("Platform: " + sys.platform)
        TempFileName=self.setNewTempFileName()
        print("Create temp Submission File: " + TempFileName)
        fileID=0
        fileID = open(TempFileName, "w")
        fileID.write("<RR_Job_File syntax_version=\"6.0\">\n")
        fileID.write("<DeleteXML>1</DeleteXML>\n")
        #scn = bpy.data.scenes["Scene"]
        scn = bpy.context.scene
        type = scn.render.image_settings.file_format
        rendertarget = type.replace("OPEN_", "")
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

        if rendertarget.endswith("_MULTILAYER"):  # i.e. EXR_MULTILAYER
            extension, rendertarget = rendertarget.rsplit("_", 1)
            extension = "." + extension.lower()
        else:
            extension = "." + rendertarget.lower()
        if extension.startswith(".avi"):
            ImageSingleOutputFile = True
            extension = ".avi"
            rendertarget = rendertarget.replace("_", "")

        extension=extension.replace(".tiff", ".tif")
        extension=extension.replace(".jpeg", ".jpg")
        
        extension=extension.replace(".quicktime", ".mov")
        extension=extension.replace(".flash", ".flv")
        extension=extension.replace(".mpeg1", ".mpg")
        extension=extension.replace(".mpeg2", ".dvd")
        extension=extension.replace(".mpeg4", ".mp4")
        
        if scn.render.filepath.startswith("//"):  # relative path
            renderOut = os.path.dirname(bpy.data.filepath) + scn.render.filepath
        else:
            renderOut = scn.render.filepath
        if renderOut.endswith('#'):
            outLen = len(renderOut) - 1
            renderPadding = outLen - next(i for i in range(outLen, 0, -1) if renderOut[i] != '#')

            if ImageSingleOutputFile:
                renderOut = "{0}{1:0{3}d}-{2:0{3}d}".format(renderOut, scn.frame_start, scn.frame_end, renderPadding)
        else:
            renderPadding = 1

        renderOut = renderOut.replace("//", "\\")
        
        writeNodeStr = self.writeNodeStr
        writeNodeInt = self.writeNodeInt
        writeNodeBool = self.writeNodeBool
        fileID.write("<Job>\n")
        writeNodeStr(fileID,"Software", "Blender")
        writeNodeInt(fileID,"Version",  bpy.app.version[0])
        writeNodeStr(fileID,"Layer", scn.render.layers[0].name)
        writeNodeStr(fileID,"SceneName",bpy.data.filepath)
        writeNodeBool(fileID,"IsActive", True )
        writeNodeBool(fileID,"ImageSingleOutputFile", ImageSingleOutputFile)
        writeNodeInt(fileID,"SeqStart",scn.frame_start)
        writeNodeInt(fileID,"SeqEnd",scn.frame_end)
        writeNodeInt(fileID,"SeqStep",scn.frame_step)
        #writeNodeStr(fileID,"ImagePreNumberLetter","_")
        writeNodeStr(fileID,"ImageDir",os.path.dirname(renderOut) ) 
        writeNodeStr(fileID,"ImageFilename",os.path.basename(renderOut))
        writeNodeInt(fileID,"ImageFramePadding", renderPadding)
        writeNodeStr(fileID,"ImageExtension",extension)
        if rendertarget in ("TGA", "RAWTGA", "JPEG", "IRIS", "IRIZ", "AVIRAW",
                            "AVIJPEG", "PNG", "BMP", "HDR", "TIFF", "EXR", "MULTILAYER",
                            "MPEG", "FRAMESERVER", "CINEON", "DPX", "DDS", "JP2"):
            writeNodeStr(fileID,"CustomFrameFormat", rendertarget)
        fileID.write("</Job>\n")
        fileID.write("</RR_Job_File>\n")
        fileID.close()
        RR_ROOT=self.get_RR_Root()
        if ((sys.platform.lower() == "win32") or (sys.platform.lower() == "win64")):
            os.system("\""+RR_ROOT+"\\win__rrSubmitter.bat\"  "+TempFileName)
        elif (sys.platform.lower() == "darwin"):
            os.system("\""+RR_ROOT+"/bin/mac64/rrSubmitter.app/Contents/MacOS/rrSubmitter\"     "+TempFileName)
        else:
            os.system("\""+RR_ROOT+"/lx__rrSubmitter.sh\"  "+TempFileName)
        return
        
    def execute(self, context):
        #print("Start Scene Submit")
        RR_ROOT = self.get_RR_Root()
        #print("Found RR_Root:"+RR_ROOT)
        print("Saving mainFile...")
        bpy.ops.wm.save_mainfile()
        self.rrSubmit()
        print("\nSubmit Scene Successfull")
        return{'FINISHED'}
 
    
    

def register():
    bpy.utils.register_class(RoyalRender_Submitter)
    bpy.utils.register_class(OBJECT_OT_SubmitScene)


def unregister():
    bpy.utils.unregister_class(RoyalRender_Submitter)
    bpy.utils.unregister_class(OBJECT_OT_SubmitScene)
    
if __name__ == "__main__":
    bpy.utils.register_module(__name__)
