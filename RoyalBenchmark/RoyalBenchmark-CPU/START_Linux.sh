#!/bin/bash

baseDir="$( cd "$( dirname "$0" )" && pwd )"
echo baseDir  is $baseDir 

export binRoot="${baseDir}/lnx"
export AppendRandomName="$1"
export PrependHostName="$2"
export AppendHostName="$3"


chmod +x "${baseDir}/lnx/rrBin/*"


rm -f /tmp/rrBench-CPU.sh
"${baseDir}/lnx/rrBin/baConvertEnvFile"  "${baseDir}/test-CPU.rrEnv" "/tmp/rrBench-CPU.sh" -shebang -bash
source  /tmp/rrBench-CPU.sh
rm -f /tmp/rrBench-CPU.sh


