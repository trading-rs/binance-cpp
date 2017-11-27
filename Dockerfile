FROM ubuntu:16.04

RUN apt-get update -qq
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y software-properties-common
RUN DEBIAN_FRONTEND=noninteractive add-apt-repository -y ppa:ubuntu-toolchain-r/test
RUN apt-get update -qq
RUN DEBIAN_FRONTEND=noninteractive apt-get install -qq g++-5
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 90
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 90
RUN update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-5 90

RUN DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y git
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y curl
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y python-dev
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libcurl4-openssl-dev
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libssl-dev

ADD https://cmake.org/files/v3.7/cmake-3.7.2-Linux-x86_64.sh /cmake-3.7.2-Linux-x86_64.sh
RUN mkdir /opt/cmake
RUN sh /cmake-3.7.2-Linux-x86_64.sh --prefix=/opt/cmake --skip-license
RUN ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake

RUN mkdir /app
WORKDIR /app
ADD . /app

RUN ./script/pre-install.sh
RUN ./script/build.sh
