#!/bin/sh
# please do chmod +x createfile.sh

if [ "$(uname)" == "Darwin" ]; then
    mkfile -n 64000  TestFile64KB
else
    dd if=/dev/zero of=64kb bs=1024 count=64000
fi
