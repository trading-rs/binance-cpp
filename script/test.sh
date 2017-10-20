#!/bin/bash
set +e
set -x

cd build
make test
if [ $? != 0 ] || [ ! -f "binance_exec" ] ; then
    exit 1
fi
