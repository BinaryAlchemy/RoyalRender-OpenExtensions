#!/bin/bash

baseDir="$( cd "$( dirname "$0" )" && pwd )"
echo baseDir  is $baseDir 

export binRoot="${baseDir}/mac"
export AppendRandomName="$1"
export PrependHostName="$2"
export AppendHostName="$3"

chmod +x "${baseDir}/mac/rrBin/all.app/Contents/MacOS/*"
chmod +x "${baseDir}/mac/rrBin/rrCopy.app/Contents/MacOS/rrCopy"


rm -f "${TMPDIR}rrBench-CPU.sh"
"${baseDir}/mac/rrBin/all.app/Contents/MacOS/baConvertEnvFile"  "${baseDir}/test-CPU.rrEnv" "${TMPDIR}rrBench-CPU.sh" -shebang -zsh
source  "${TMPDIR}rrBench-CPU.sh"
rm -f "${TMPDIR}rrBench-CPU.sh"