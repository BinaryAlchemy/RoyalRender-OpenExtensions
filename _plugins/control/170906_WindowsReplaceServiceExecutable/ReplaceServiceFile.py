import os
import shutil
client= rr.getClient()

localpath="\\\\"+client.name()+"\\C$\\Program Files (x86)\\rrService\\rrAutostartservice.exe"
if (os.path.exists(localpath)):
    print(localpath)
    shutil.copyfile("\\\\AIR\\Royal_Render\\bin\\win\\rrAutostartservice.exe",localpath)
    rrGlobal.refreshUI()
    
        
localpath="\\\\"+client.name()+"\\C$\\Program Files\\rrService\\rrAutostartservice.exe"
if (os.path.exists(localpath)):
    print(localpath)
    shutil.copyfile("\\\\AIR\\Royal_Render\\bin\\win64\\rrAutostartservice.exe",localpath)
    rrGlobal.refreshUI()
