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

echo "generating sdl2 project for mingw..."
mkdir lib/sdl2/_CMAKE
cd lib/sdl2/_CMAKE
cmake -G "Unix Makefiles" -DCMAKE_C_FLAGS=-m32 -DCMAKE_BUILD_TYPE=MinSizeRel -DSDL_SHARED=OFF -DSDL_ATOMIC=OFF -DSDL_CPUINFO=OFF -DSDL_DLOPEN=OFF -DSDL_FILE=OFF -DSDL_FILESYSTEM=OFF -DSDL_RENDER=OFF -DSDL_THREADS=OFF -DVIDEO_VULKAN=OFF -DVIDEO_OPENGLES=OFF ..

echo "building sdl2..."
mingw32-make
cd ../../..

echo "generating tau project for gcc..."
mkdir _CMAKE
cd _CMAKE
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel ..

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
