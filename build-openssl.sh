#!/bin/bash
set +e
set -x

dir=$(pwd)
mkdir -p library_openssl/ssl
cd ./libs/openssl
# https://github.com/openssl/openssl/blob/master/INSTALL
./config --prefix=$dir/library_openssl --openssldir=$dir/library_openssl/ssl
make
make test
make install
