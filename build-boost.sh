#!/bin/bash
set +e
set -x

rm -rf library_boost
dir=$(pwd)
mkdir library_boost
cd ./libs/boost
# https://github.com/boostorg/boost/wiki/Getting-Started
# https://stackoverflow.com/questions/104322/how-do-you-install-boost-on-macos
./bootstrap.sh --prefix=$dir/library_boost
./b2
./b2 headers
./b2 install
