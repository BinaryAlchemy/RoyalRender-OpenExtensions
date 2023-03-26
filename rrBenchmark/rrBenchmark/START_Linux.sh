#!/bin/bash

baseDir="$( cd "$( dirname "$0" )" && pwd )"
echo baseDir  is $baseDir 

export binDir="${baseDir}/lnx"
export PrependHostName="$1"
export AppendHostName="$2"

chmod +x "${baseDir}/lnx/rrBin/baConvertEnvFile"
chmod +x "${baseDir}/lnx/rrBin/baCPUInfo"
chmod +x "${baseDir}/lnx/rrBin/rrCopy"
chmod +x "${baseDir}/lnx/rrBin/rrParseOutput"
chmod +x "${baseDir}/lnx/rrBin/rrTest_CpuBenchmark"
chmod +x "${baseDir}/lnx/rrBin/rrTestMachine"

chmod +x "${baseDir}/lnx/arnold/bin/kick"
chmod +x "${baseDir}/lnx/blender/blender"
chmod +x "${baseDir}/lnx/vray/vray-benchmark-5.02.01"


rm -f /tmp/RR_test.sh
"${baseDir}/lnx/rrBin/baConvertEnvFile"  "${baseDir}/test.rrEnv" "/tmp/RR_test.sh" -shebang -bash
source  /tmp/RR_test.sh
rm -f /tmp/RR_test.sh


