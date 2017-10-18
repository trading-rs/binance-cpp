#!/bin/bash
set +e
set -x

cd ./libs/boost
# https://github.com/boostorg/boost/wiki/Getting-Started
./bootstrap.sh
./b2 headers
