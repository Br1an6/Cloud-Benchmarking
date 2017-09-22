#!/bin/sh
# please do chmod +x createfile.sh

if [ "$(uname)" == "Darwin" ]; then
    mkfile -n 20m  TestFile20MB
else
    dd if=/dev/zero of=TestFile20MB bs=1024 count=$[20*1024]
fi
