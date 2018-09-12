#!/bin/sh
cd `dirname $0`

echo "creating lua wrappers..."
swig -lua -o src/wrap_color.c stuff/color.i
swig -lua -o src/wrap_input.c stuff/input.i
swig -lua -o src/wrap_light.c stuff/light.i
swig -lua -o src/wrap_log.c stuff/log.i
swig -lua -o src/wrap_material.c stuff/material.i
swig -lua -o src/wrap_object.c stuff/object.i
swig -lua -o src/wrap_pixmap.c stuff/pixmap.i
swig -lua -o src/wrap_screen.c stuff/screen.i
swig -lua -o src/wrap_texture.c stuff/texture.i
swig -lua -o src/wrap_viewer.c stuff/viewer.i

echo "generating project for gcc..."
mkdir _CMAKE
cd _CMAKE
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel ..

echo "building..."
make
cd ..

echo "moving to _build dir..."
mkdir _build
mv _CMAKE/tau _build/tau

echo "running..."
cd _build
./tau data/angel.lua
./tau data/fog.lua
./tau data/helloworld.lua
./tau data/hoverbike.lua
./tau data/md2.lua
./tau data/rotatingcube.lua
./tau data/specular.lua

echo "done."
