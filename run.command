#!/bin/sh
cd `dirname $0`

echo "running examples..."
cd _build
./micron data/angel.lua
./micron data/billboards.lua
./micron data/collisions.lua
./micron data/fog.lua
./micron data/helloworld.lua
./micron data/hoverbike.lua
./micron data/md2.lua
./micron data/primitives.lua
./micron data/rotatingcube.lua
./micron data/specular.lua

echo "done."
