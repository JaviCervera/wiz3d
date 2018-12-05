#!/bin/sh
cd `dirname $0`

echo "creating lua wrappers..."
swig -lua -o src/wrap_colbox.c stuff/colbox.i
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

echo "generating glfw project for gcc..."
mkdir lib/glfw/_CMAKE
cd lib/glfw/_CMAKE
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_INSTALL=OFF ..

echo "building glfw..."
make
cd ../../..

echo "generating openal-soft project for gcc..."
mkdir lib/openal-soft/_CMAKE
cd lib/openal-soft/_CMAKE
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -DALSOFT_EXAMPLES=OFF -DALSOFT_INSTALL=OFF -DALSOFT_NO_CONFIG_UTIL=ON -DALSOFT_STATIC_LIBGCC=ON -DALSOFT_TESTS=OFF -DALSOFT_UTILS=OFF ..

echo "building openal-soft..."
make
cd ../../..

echo "generating micron project for gcc..."
mkdir _CMAKE
cd _CMAKE
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel ..

echo "building micron..."
make
cd ..

echo "moving micron to _build dir..."
mkdir _build
mv _CMAKE/micron _build/micron

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
