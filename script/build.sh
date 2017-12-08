#!/bin/bash
set +e
set -x

rm -rf build
mkdir build && cd build
if [ "$RUNTIME" = "DOCKER" ]
then
    cmake -DNEEDCURL:BOOL=OFF ..
else
    cmake ..
fi
make
