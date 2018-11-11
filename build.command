#!/bin/sh
cd `dirname $0`

echo "creating lua wrappers..."
swig -lua -o src/wrap_color.c stuff/color.i
swig -lua -o src/wrap_input.c stuff/input.i
swig -lua -o src/wrap_light.c stuff/light.i
swig -lua -o src/wrap_log.c stuff/log.i
swig -lua -o src/wrap_material.c stuff/material.i
swig -lua -o src/wrap_memory.c stuff/memory.i
swig -lua -o src/wrap_object.c stuff/object.i
swig -lua -o src/wrap_pixmap.c stuff/pixmap.i
swig -lua -o src/wrap_screen.c stuff/screen.i
swig -lua -o src/wrap_texture.c stuff/texture.i
swig -lua -o src/wrap_viewer.c stuff/viewer.i

echo "generating glfw project for mingw..."
mkdir lib/glfw/_CMAKE
cd lib/glfw/_CMAKE
cmake -G "Unix Makefiles" -DCMAKE_OSX_DEPLOYMENT_TARGET=10.9 -DCMAKE_BUILD_TYPE=MinSizeRel -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_INSTALL=OFF ..

echo "building glfw..."
make
cd ../../..

echo "generating tau project for gcc..."
mkdir _CMAKE
cd _CMAKE
cmake -G "Unix Makefiles" -DCMAKE_OSX_DEPLOYMENT_TARGET=10.9 -DCMAKE_BUILD_TYPE=MinSizeRel ..

echo "building tau..."
make
cd ..

echo "moving tau to _build dir..."
mkdir _build
mv _CMAKE/tau _build/tau

echo "running examples..."
cd _build
./tau data/angel.lua
./tau data/billboards.lua
./tau data/fog.lua
./tau data/helloworld.lua
./tau data/hoverbike.lua
./tau data/md2.lua
./tau data/rotatingcube.lua
./tau data/specular.lua

echo "done."
