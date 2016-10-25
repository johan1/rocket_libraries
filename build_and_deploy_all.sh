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
LIBRARIES="$LIBRARIES glew"

for LIBRARY in $LIBRARIES; do
	echo Building and deploying $LIBRARY...
	cd $LIBRARY;
	if [ -f "project.mk" ]; then
		rocket_prepare
	fi
	make clean deploy;
	cd -
done

