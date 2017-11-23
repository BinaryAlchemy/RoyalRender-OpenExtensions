import os
import shutil
client= rr.getClient()

print("testing "+client.name()+"... ")
rrGlobal.refreshUI()
localpath="\\\\"+client.name()+"\\C$\\Program Files\\"
if (os.path.exists(localpath)):
    print("    ...online... ")
    localpath="\\\\"+client.name()+"\\C$\\Program Files (x86)\\rrService\\rrAutostartservice.exe"
    if (os.path.exists(localpath)):
        print("Renaming  "+localpath)
        rrGlobal.refreshUI()
        shutil.move(localpath,localpath+"_old2")
        print("Replacing  "+localpath)
        rrGlobal.refreshUI()
        shutil.copyfile("\\\\AIR\\Royal_Render\\bin\\win\\rrAutostartservice.exe",localpath)
    localpath="\\\\"+client.name()+"\\C$\\Program Files\\rrService\\rrAutostartservice.exe"
    if (os.path.exists(localpath)):
        print("Renaming  "+localpath)
        rrGlobal.refreshUI()
        shutil.move(localpath,localpath+"_old2")
        print("Replacing  "+localpath)
        shutil.copyfile("\\\\AIR\\Royal_Render\\bin\\win64\\rrAutostartservice.exe",localpath)
        
