#!/bin/sh

REPOSITORY_PATH=$HOME/.rocket_tools/repository
DEPLOY_PATH=$REPOSITORY_PATH/openal-soft/1.17.2

mkdir -p $DEPLOY_PATH
cp -r openal-soft-1.17.2/include $DEPLOY_PATH

mkdir -p $DEPLOY_PATH/lib/host
cp openal-soft-1.17.2/build/host/libopenal.so $DEPLOY_PATH/lib/host

mkdir -p $DEPLOY_PATH/lib/i686-w64-mingw32
mkdir -p $DEPLOY_PATH/bin/i686-w64-mingw32
cp openal-soft-1.17.2/build/windows/libOpenAL32.dll.a $DEPLOY_PATH/lib/i686-w64-mingw32
cp openal-soft-1.17.2/build/windows/OpenAL32.dll $DEPLOY_PATH/bin/i686-w64-mingw32
cp openal-soft-1.17.2/build/windows/libcommon.a $DEPLOY_PATH/lib/i686-w64-mingw32

cp library.mk $DEPLOY_PATH
