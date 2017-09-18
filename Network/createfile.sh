#!/bin/sh
# please do chmod +x createfile.sh

if [ "$(uname)" == "Darwin" ]; then
    mkfile -n 64000  TestFile64KB
else
    dd if=/dev/zero of=TestFile64KB bs=1000 count=64
fi
