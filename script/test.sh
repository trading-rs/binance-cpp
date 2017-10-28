#!/bin/bash
set +e
set -x

cd build
make test
if [ $? != 0 ] || [ ! -f "binance_example" ] || [ ! -f "depth_cache_example" ] ; then
    exit 1
fi
