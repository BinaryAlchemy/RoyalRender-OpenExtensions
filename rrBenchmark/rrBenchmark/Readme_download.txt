
Arnold for Maya 2022 version 5.1.3.3 

Windows:
https://arnoldrenderer.com/download/archive/arnold-for-maya/5.1.3.3/eula/?id=4802

Note: The installer has a bug.
Please copy your file c:\Program Files\Common Files\Autodesk Shared\Modules\Maya\2022\mtoa.mod to a different location.

Execute the installer.
Un-check "configure for Maya".
Change the installation path to some temp path.

After installation, copy the file mtoa.mod back.
(Otherwise Maya does not find your old MtoA)

Copy the contents of the folder into  ....\rrBenchmark\win\arnold
Delete the file ....\rrBenchmark\win\arnold\bin\ai_renderview.dll (Just that it never tries to load any UI lib)

Resulting executable: ....\rrBenchmark\win\arnold\bin\kick.exe

Optional in case this package should be send to some other location:
You may want to remove the folder ....\rrBenchmark\win\arnold\license\installer\
You may want to remove the folder ....\rrBenchmark\win\arnold\docs\



Linux:
https://arnoldrenderer.com/download/archive/arnold-for-maya/5.1.3.3/eula/?id=4803
Execute  MtoA-5.1.3.3-linux-2022.run 
Type accept
Press key 2  to extract the packae only
Enter path /tmp/MtoA
Move the contents of the folder /tmp/MtoA into  ..../rrBenchmark/lnx/arnold
Delete the file ....\rrBenchmark\lnx\arnold\bin\libai_renderview.so (Just that it never tries to load any UI lib)

Resulting executable: ..../rrBenchmark/lnx/arnold/bin/kick


Optional in case this package should be send to some other location:
You may want to remove the folder ....\rrBenchmark\lnx\arnold\license\installer\
You may want to remove the folder ....\rrBenchmark\lnx\arnold\docs\


MacOS:
https://arnoldrenderer.com/download/archive/arnold-for-maya/5.1.3.3/eula/?id=4804

Execute the installer.
Copy all files and folders from /Applications/Autodesk/Arnold/mtoa/2022 into ..../rrBenchmark/mac/arnold/

Resulting executable: ..../rrBenchmark/mac/arnold/bin/kick



VRay benchmark 5.02.01 (update 2.1)
Windows "CLI" version: 
https://download.chaos.com/api/v1/builds/21356/download

Copy the file into ....\rrBenchmark\win\vray\
Resulting executable: ....\rrBenchmark\win\vray\vray-benchmark-5.02.01-cli.exe

Linux:
https://download.chaos.com/api/v1/builds/21358/download
Copy the file into ....\rrBenchmark\win\vray\
Resulting executable: ....\rrBenchmark\lx\vray\vray-benchmark-5.02.01


MacOS:
https://download.chaos.com/api/v1/builds/21363/download
Open the folder ..../rrBenchmark/mac/vray in finder.
Open the downloaded package.
DragNDrop "V-Ray Benchmark" from the package into ..../rrBenchmark/mac/vray




Blender 3.4.1
Windows
Download https://www.blender.org/download/release/Blender3.4/blender-3.4.1-windows-x64.zip/
Extract the zip and copy the CONTENTS of folder blender-3.4.1-windows-x64 into ....\rrBenchmark\win\blender\
Resulting executable: ....\rrBenchmark\win\blender\blender.exe

Optional in case this package should be send to some other location:
You may want to remove the blender.pdb file.
It is required for crash reports only.

Linux:
https://www.blender.org/download/release/Blender3.4/blender-3.4.1-linux-x64.tar.xz/
Extract the zip and copy the CONTENTS of folder blender-3.4.1-linux-x64 into ....\rrBenchmark\win\blender\
Resulting executable: ....\rrBenchmark\lnx\blender\blender
Please rename 
..../rrBenchmark\lnx\blender\lib\libsycl.so.6.1.0-0  into libsycl.so.6  (and overwrite the old file)
..../rrBenchmark\lnx\blender\lib\mesa\libglapi.so.0.0 into libglapi.so.0
..../rrBenchmark\lnx\blender\lib\mesa\libGLU.so.1.3.1 into libGLU.so.1
..../rrBenchmark\lnx\blender\lib\mesa\libGL.so.1.5.0 into libGL.so.1

MacOS:
https://www.blender.org/download/release/Blender3.4/blender-3.4.1-macos-x64.dmg/
Open the folder ..../rrBenchmark/mac/blender in finder.
Open the downloaded package.
DragNDrop "Blender" from the package into ..../rrBenchmark/mac/vray




CineBench23
Windows: 
https://installer.maxon.net/cinebench/CinebenchR23.zip

Extract the zip file into ....\rrBenchmark\win\CinebenchR23\
Resulting executable: ....\rrBenchmark\win\CinebenchR23\Cinebench.exe

MacOS:
https://installer.maxon.net/cinebench/CinebenchR23.dmg
Open the folder ..../rrBenchmark/mac/CinebenchR23 in finder.
Open the downloaded package.
DragNDrop "Cinebench" from the package into ..../rrBenchmark/mac/CinebenchR23






OctaneBench 2020.1
https://render.otoy.com/downloads/a/61/d26aef36-44d9-4434-b726-413ecde76ecf/OctaneBench_2020_1_5_win.zip
https://render.otoy.com/downloads/a/61/2d40eddf-65a5-4c96-bc10-ab527f31dbee/OctaneBench_2020_1_5_linux.zip
https://render.otoy.com/downloads/a/159/18face6a-d932-44d1-b722-d9100c5f0a08/OctaneBench_2020_1_5_macos.dmg


Redshift:







