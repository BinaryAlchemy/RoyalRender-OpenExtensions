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
        layout.label("SubmitSceneValues: ")
        layout.label("StartFrame: " + str(scn.frame_start))
        layout.label("EndFrame: " + str(scn.frame_end))
        layout.label("ImageType: " + type)
        layout.label("ImageName: " + os.path.basename(renderOut))
        layout.label("RenderDir: " +  os.path.dirname(renderOut))  
        #layout.label()      
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
        rendertarget = type
        extension = "."+rendertarget.lower()
        extension.replace("open_", "");
        renderOut = os.path.dirname(bpy.data.filepath) + scn.render.filepath
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
        writeNodeInt(fileID,"SeqStart",scn.frame_start)
        writeNodeInt(fileID,"SeqEnd",scn.frame_end)
        writeNodeInt(fileID,"SeqStep",scn.frame_step)
        #writeNodeStr(fileID,"ImagePreNumberLetter","_")
        writeNodeStr(fileID,"ImageDir",os.path.dirname(renderOut) ) 
        writeNodeStr(fileID,"ImageFilename",os.path.basename(renderOut))
        writeNodeStr(fileID,"ImageExtension",extension)
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
