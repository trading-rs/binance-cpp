#!/bin/bash
set -e
set -x

SHA1=`git rev-parse HEAD`

IMAGE_NAME="zjhsdtc/binance-cpp:latest"
IMAGE_NAME_TAG="zjhsdtc/binance-cpp:${SHA1}"

docker login -u $DOCKER_USER -p $DOCKER_PASSWORD

docker build --tag $IMAGE_NAME -f Dockerfile .
docker tag $IMAGE_NAME $IMAGE_NAME_TAG
docker push $IMAGE_NAME_TAG
docker push $IMAGE_NAME
docker rmi -f $IMAGE_NAME_TAG
docker rmi -f $IMAGE_NAME

DANGLING_IMAGES=`docker images -f "dangling=true" -q`
if [[ -n "$DANGLING_IMAGES" ]]; then
    docker rmi -f $DANGLING_IMAGES
fi
