@echo off

echo creating lua wrappers...
stuff\swig.exe -lua -o src/wrap_colbox.c stuff/colbox.i
stuff\swig.exe -lua -o src/wrap_color.c stuff/color.i
stuff\swig.exe -lua -o src/wrap_input.c stuff/input.i
stuff\swig.exe -lua -o src/wrap_light.c stuff/light.i
stuff\swig.exe -lua -o src/wrap_log.c stuff/log.i
stuff\swig.exe -lua -o src/wrap_material.c stuff/material.i
stuff\swig.exe -lua -o src/wrap_memory.c stuff/memory.i
stuff\swig.exe -lua -o src/wrap_object.c stuff/object.i
stuff\swig.exe -lua -o src/wrap_pixmap.c stuff/pixmap.i
stuff\swig.exe -lua -o src/wrap_screen.c stuff/screen.i
stuff\swig.exe -lua -o src/wrap_sound.c stuff/sound.i
stuff\swig.exe -lua -o src/wrap_texture.c stuff/texture.i
stuff\swig.exe -lua -o src/wrap_viewer.c stuff/viewer.i

echo generating allegro project for mingw...
cd lib/allegro
mkdir _CMAKE
cd _CMAKE
cmake -G "MinGW Makefiles" -DCMAKE_C_FLAGS=-m32 -DCMAKE_BUILD_TYPE=MinSizeRel -DSHARED=OFF -DWANT_COLOR=OFF -DWANT_D3D=OFF -DWANT_DEMO=OFF -DWANT_DOCS=OFF -DWANT_EXAMPLES=OFF -DWANT_FLAC=OFF -DWANT_FONT=OFF -DWANT_IMAGE=OFF -DWANT_MEMFILE=OFF -DWANT_MODAUDIO=OFF -DWANT_MONOLITH=ON -DWANT_NATIVE_DIALOG=OFF -DWANT_OPENAL=OFF -DWANT_OPENSL=OFF -DWANT_OPUS=OFF -DWANT_OSS=OFF -DWANT_PHYSFS=OFF -DWANT_PRIMITIVES=OFF -DWANT_RELEASE_LOGGING=OFF -DWANT_STATIC_RUNTIME=ON -DWANT_TESTS=OFF -DWANT_TTF=OFF -DWANT_VIDEO=OFF -DWANT_VORBIS=OFF ..

echo building allegro...
mingw32-make
cd ../../..

echo generating glfw project for mingw...
cd lib/glfw
mkdir _CMAKE
cd _CMAKE
cmake -G "MinGW Makefiles" -DCMAKE_C_FLAGS=-m32 -DCMAKE_BUILD_TYPE=MinSizeRel -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_INSTALL=OFF ..

echo building glfw...
mingw32-make
cd ../../..

echo generating micron project for mingw...
mkdir _CMAKE
cd _CMAKE
cmake -G "MinGW Makefiles" -DCMAKE_C_FLAGS=-m32 -DCMAKE_BUILD_TYPE=MinSizeRel ..

echo building micron...
mingw32-make
cd ..

echo moving micron to _build dir...
mkdir _build
move "_CMAKE\micron.exe" "_build"

pause
