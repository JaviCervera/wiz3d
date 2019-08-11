#!/bin/sh
cd `dirname $0`

echo "[**creating folders for cmake**]"
mkdir _CMAKE
mkdir _CMAKE/_ALLEGRO
mkdir _CMAKE/_GLFW
mkdir _CMAKE/_SDL2

echo "[**building allegro**]"
cd _CMAKE/_ALLEGRO
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -DSHARED=OFF -DWANT_COLOR=OFF -DWANT_D3D=OFF -DWANT_DEMO=OFF -DWANT_DOCS=OFF -DWANT_EXAMPLES=OFF -DWANT_FLAC=OFF -DWANT_FONT=OFF -DWANT_IMAGE=OFF -DWANT_MEMFILE=OFF -DWANT_MODAUDIO=OFF -DWANT_MONOLITH=ON -DWANT_OPENAL=OFF -DWANT_OPENSL=OFF -DWANT_OPUS=OFF -DWANT_OSS=OFF -DWANT_PHYSFS=OFF -DWANT_PRIMITIVES=OFF -DWANT_RELEASE_LOGGING=OFF -DWANT_STATIC_RUNTIME=ON -DWANT_TESTS=OFF -DWANT_TTF=OFF -DWANT_VIDEO=OFF -DWANT_VORBIS=OFF ../../lib/allegro
make
cd ../..

echo "[**building glfw**]"
cd _CMAKE/_GLFW
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_INSTALL=OFF ../../lib/glfw
make
cd ../..

echo "[**building sdl2**]"
cd _CMAKE/_SDL2
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel -DSDL_SHARED=OFF -DSDL_ATOMIC=OFF -DSDL_CPUINFO=OFF -DSDL_DLOPEN=OFF -DSDL_FILE=OFF -DSDL_FILESYSTEM=OFF -DSDL_RENDER=OFF -DSDL_THREADS=OFF -DVIDEO_VULKAN=OFF -DVIDEO_OPENGLES=OFF -DVIDEO_WAYLAND=OFF ../../lib/sdl2
make
cd ../..

echo "[**building beam**]"
cd _CMAKE
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel ..
make
cd ..

echo "[**moving beam to _build dir**]"
mkdir _build
mv _CMAKE/libbeam.so _build/libbeam.so

echo "done."
