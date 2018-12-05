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

echo generating glfw project for mingw...
cd lib/glfw
mkdir _CMAKE
cd _CMAKE
cmake -G "MinGW Makefiles" -DCMAKE_C_FLAGS=-m32 -DCMAKE_BUILD_TYPE=MinSizeRel -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_INSTALL=OFF ..

echo building glfw...
mingw32-make
cd ../../..

echo generating openal-soft project for mingw...
cd lib/openal-soft
mkdir _CMAKE
cd _CMAKE
cmake -G "MinGW Makefiles" -DCMAKE_C_FLAGS=-m32 -DCMAKE_BUILD_TYPE=MinSizeRel -DALSOFT_EXAMPLES=OFF -DALSOFT_INSTALL=OFF -DALSOFT_NO_CONFIG_UTIL=ON -DALSOFT_STATIC_LIBGCC=ON -DALSOFT_TESTS=OFF -DALSOFT_UTILS=OFF ..

echo building openal-soft...
mingw32-make

echo renaming openal-soft static lib...
rename libOpenAL32.dll.a libOpenAL32.a
cd ../../..

echo moving openal-soft to _build dir...
mkdir _build
move "lib\openal-soft\_CMAKE\OpenAL32.dll" "_build"

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

rem echo compressing...
rem upx.exe _build/micron.exe
rem upx.exe --brute _build/micron.exe

echo running examples...
cd _build
micron.exe data/angel.lua
micron.exe data/billboards.lua
micron.exe data/collisions.lua
micron.exe data/fog.lua
micron.exe data/helloworld.lua
micron.exe data/hoverbike.lua
micron.exe data/md2.lua
micron.exe data/primitives.lua
micron.exe data/rotatingcube.lua
micron.exe data/specular.lua
pause
