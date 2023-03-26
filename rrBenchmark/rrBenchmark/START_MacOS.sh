#!/bin/bash

baseDir="$( cd "$( dirname "$0" )" && pwd )"
echo baseDir  is $baseDir 

export binDir="${baseDir}/mac"
export PrependHostName="$1"
export AppendHostName="$2"

chmod +x "${baseDir}/mac/rrBin/all.app/Contents/MacOS/baConvertEnvFile"
chmod +x "${baseDir}/mac/rrBin/all.app/Contents/MacOS/baCPUInfo"
chmod +x "${baseDir}/mac/rrBin/all.app/Contents/MacOS/rrCopy"
chmod +x "${baseDir}/mac/rrBin/all.app/Contents/MacOS/rrParseOutput"
chmod +x "${baseDir}/mac/rrBin/all.app/Contents/MacOS/rrTest_CpuBenchmark"
chmod +x "${baseDir}/mac/rrBin/all.app/Contents/MacOS/rrTestMachine"

chmod +x "${baseDir}/mac/arnold/bin/kick"
chmod +x "${baseDir}/mac/Blender.app/Contents/MacOS/Blender"
chmod +x "${baseDir}/mac/vray/V-Ray Benchmark.app/Contents/MacOS/V-Ray Benchmark"

rm -f "${TMPDIR}RR_test.sh"
"${baseDir}/mac/rrBin/all.app/Contents/MacOS/baConvertEnvFile"  "${baseDir}/test.rrEnv" "${TMPDIR}RR_test.sh" -shebang -zsh
source  "${TMPDIR}RR_test.sh"
rm -f "${TMPDIR}RR_test.sh"