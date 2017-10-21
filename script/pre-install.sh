#!/bin/bash
set +e
set -x

git submodule update --init --recursive
./build-openssl.sh
./build-boost.sh
