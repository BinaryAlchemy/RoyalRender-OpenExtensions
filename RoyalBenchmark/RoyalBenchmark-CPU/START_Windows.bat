@prompt $T$g
set baseDir=%~dp0
echo baseDir is %baseDir%
set "binRoot=%baseDir%win"
set "AppendRandomName=%1"
set "PrependHostName=%2"
set "AppendHostName=%3"

echo %time%
"%baseDir%win\rrBin\baConvertEnvFile.exe"  "%baseDir%test-CPU.rrEnv" "%TEMP%\rrBench-CPU.bat"
call  %TEMP%\rrBench-CPU.bat
echo %time%
del %TEMP%\rrBench-CPU.bat

rem shutdown /s
