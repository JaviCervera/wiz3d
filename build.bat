@echo off

echo creating lua wrappers...
stuff\swig.exe -lua -o src/wrap_color.c stuff/color.i
stuff\swig.exe -lua -o src/wrap_input.c stuff/input.i
stuff\swig.exe -lua -o src/wrap_light.c stuff/light.i
stuff\swig.exe -lua -o src/wrap_log.c stuff/log.i
stuff\swig.exe -lua -o src/wrap_material.c stuff/material.i
stuff\swig.exe -lua -o src/wrap_memory.c stuff/memory.i
stuff\swig.exe -lua -o src/wrap_object.c stuff/object.i
stuff\swig.exe -lua -o src/wrap_pixmap.c stuff/pixmap.i
stuff\swig.exe -lua -o src/wrap_screen.c stuff/screen.i
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

echo generating tau project for mingw...
mkdir _CMAKE
cd _CMAKE
cmake -G "MinGW Makefiles" -DCMAKE_C_FLAGS=-m32 -DCMAKE_BUILD_TYPE=MinSizeRel ..

echo building tau...
mingw32-make
cd ..

echo moving tau to _build dir...
mkdir _build
move "_CMAKE\tau.exe" "_build"

rem echo compressing...
rem upx.exe _build/tau.exe
rem upx.exe --brute _build/tau.exe

echo running examples...
cd _build
tau.exe data/angel.lua
tau.exe data/billboards.lua
tau.exe data/fog.lua
tau.exe data/helloworld.lua
tau.exe data/hoverbike.lua
tau.exe data/md2.lua
tau.exe data/rotatingcube.lua
tau.exe data/specular.lua
pause
