@prompt $T$g
set baseDir=%~dp0
echo baseDir is %baseDir%
set "binDir=%baseDir%win"
set "PrependHostName=%1"
set "AppendHostName=%2"

echo %time%
"%baseDir%win\rrBin\baConvertEnvFile.exe"  "%baseDir%test.rrEnv" "%TEMP%\RR_test.bat"
call  %TEMP%\RR_test.bat
echo %time%
del %TEMP%\RR_test.bat