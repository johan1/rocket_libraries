#!/bin/bash

LIBRARIES="BoostHeaders"
LIBRARIES="$LIBRARIES BoostSystem"
LIBRARIES="$LIBRARIES BoostFileSystem"
LIBRARIES="$LIBRARIES BoostChrono"
LIBRARIES="$LIBRARIES BoostAtomic"
LIBRARIES="$LIBRARIES BoostThread"
LIBRARIES="$LIBRARIES Box2D"
LIBRARIES="$LIBRARIES glm"
LIBRARIES="$LIBRARIES cppjson"
LIBRARIES="$LIBRARIES libogg"
LIBRARIES="$LIBRARIES libpng15"
LIBRARIES="$LIBRARIES libvorbis"
LIBRARIES="$LIBRARIES freetype"
LIBRARIES="$LIBRARIES jsoncpp"
LIBRARIES="$LIBRARIES rocketcore"

for LIBRARY in $LIBRARIES; do
	echo Building and deploying $LIBRARY...
	cd $LIBRARY && rocket_build clean deploy && cd -
done

