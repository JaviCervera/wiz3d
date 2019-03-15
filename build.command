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
swig -lua -o src/wrap_sound.c stuff/sound.i
swig -lua -o src/wrap_texture.c stuff/texture.i
swig -lua -o src/wrap_viewer.c stuff/viewer.i

echo "generating allegro project for gcc..."
mkdir lib/allegro/_CMAKE
cd lib/allegro/_CMAKE
cmake -G "Unix Makefiles" -DCMAKE_OSX_DEPLOYMENT_TARGET=10.9 -DCMAKE_BUILD_TYPE=MinSizeRel -DSHARED=OFF -DWANT_COLOR=OFF -DWANT_D3D=OFF -DWANT_DEMO=OFF -DWANT_DOCS=OFF -DWANT_EXAMPLES=OFF -DWANT_FLAC=OFF -DWANT_FONT=OFF -DWANT_IMAGE=OFF -DWANT_MEMFILE=OFF -DWANT_MODAUDIO=OFF -DWANT_MONOLITH=ON -DWANT_OPENAL=OFF -DWANT_OPENSL=OFF -DWANT_OPUS=OFF -DWANT_OSS=OFF -DWANT_PHYSFS=OFF -DWANT_PRIMITIVES=OFF -DWANT_RELEASE_LOGGING=OFF -DWANT_STATIC_RUNTIME=ON -DWANT_TESTS=OFF -DWANT_TTF=OFF -DWANT_VIDEO=OFF -DWANT_VORBIS=OFF ..

echo "building allegro..."
make
cd ../../..

echo "generating micron project for gcc..."
mkdir _CMAKE
cd _CMAKE
cmake -G "Unix Makefiles" -DCMAKE_OSX_DEPLOYMENT_TARGET=10.9 -DCMAKE_BUILD_TYPE=MinSizeRel ..

echo "building micron..."
make
cd ..

echo "moving micron to _build dir..."
mkdir _build
mv _CMAKE/micron _build/micron

echo "done."
