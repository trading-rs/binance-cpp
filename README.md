# Binance API Wrapper for Modern C++

[![Build Status](https://travis-ci.org/zjhmale/binance-cpp.svg?branch=master)](https://travis-ci.org/zjhmale/binance-cpp)

## Features

* Easy to use C++ APIs.
* Fully armed with C++11/14 standards.
* Abstraction of all the response data types.
* Implementation of all the up-to-date endpoints.
* Detailed examples to demonstrate how to use this library.

## Getting Started

### Prerequisite

```sh
./script/pre-install.sh
```

### Setup Environment Variables (optional)

```
export BINANCE_API_KEY="<api_key>"
export BINANCE_API_SECRET="<secret_key>"
```

### Build

```
./script/build.sh
```

### Test

```
./script/build.sh
./script/test.sh
```

### Documentation

![API DOCUMENTATION](./DOCUMENT.md)

### Examples

* ![example.cc](./example/example.cc)
* ![depth_cache_example.cc](./example/depth_cache_example.cc)
