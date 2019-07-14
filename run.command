#!/bin/sh
cd `dirname $0`

echo "running examples..."
cd _build
./beam data/angel.lua
./beam data/billboards.lua
./beam data/collisions.lua
./beam data/fog.lua
./beam data/helloworld.lua
./beam data/hoverbike.lua
./beam data/md2.lua
./beam data/primitives.lua
./beam data/rotatingcube.lua
./beam data/specular.lua

echo "done."
