FROM ubuntu:16.04

RUN apt-get update -qq && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y software-properties-common && \
    DEBIAN_FRONTEND=noninteractive add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    DEBIAN_FRONTEND=noninteractive apt-get install -qq g++-5 && \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 90 && \
    update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-5 90 && \
    update-alternatives --install /usr/bin/c++ c++ /usr/bin/g++-5 90 && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y build-essential && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y git && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y curl && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y python-dev && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y libcurl4-openssl-dev && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y libssl-dev && \
    rm -rf /var/lib/apt/lists/*

ADD https://cmake.org/files/v3.7/cmake-3.7.2-Linux-x86_64.sh /cmake-3.7.2-Linux-x86_64.sh
RUN mkdir /opt/cmake && \
    sh /cmake-3.7.2-Linux-x86_64.sh --prefix=/opt/cmake --skip-license && \
    ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake

RUN mkdir /app
WORKDIR /app
ADD . /app

ENV BINANCE_API_KEY="MhRunnc21XQiJXmzfOXzDEE40f7NtoObkXz5Dd22xYai5adRSBEOCCjYpdSYZjII"
ENV BINANCE_API_SECRET="DgA1H591E8qyVRQgSVhdo2QOP0BC90nzDmL8UXDb4tO0ZajBkAL8ijXzYDmyEPgj"

RUN ./script/pre-install.sh && \
    RUNTIME=DOCKER ./script/build.sh && \
    ./script/test.sh
