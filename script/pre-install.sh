#!/bin/bash
set +e
set -x

git submodule update --init --recursive
./script/build-openssl.sh
./script/build-boost.sh
