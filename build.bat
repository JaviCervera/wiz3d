@echo off

echo creating lua wrappers...
stuff\swig.exe -lua -o src/wrap_color.c stuff/color.i
stuff\swig.exe -lua -o src/wrap_input.c stuff/input.i
stuff\swig.exe -lua -o src/wrap_light.c stuff/light.i
stuff\swig.exe -lua -o src/wrap_log.c stuff/log.i
stuff\swig.exe -lua -o src/wrap_material.c stuff/material.i
stuff\swig.exe -lua -o src/wrap_object.c stuff/object.i
stuff\swig.exe -lua -o src/wrap_screen.c stuff/screen.i
stuff\swig.exe -lua -o src/wrap_texture.c stuff/texture.i
stuff\swig.exe -lua -o src/wrap_viewer.c stuff/viewer.i

echo generating project for mingw...
mkdir _CMAKE
cd _CMAKE
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=MinSizeRel ..

echo building...
mingw32-make
cd ..

echo moving to _build dir...
mkdir _build
move "_CMAKE\tau.exe" "_build"

echo compressing...
upx.exe _build/bin/tau.exe
rem upx.exe --brute _build/bin/tau.exe

echo running...
cd _build
tau.exe data/angel.lua
tau.exe data/fog.lua
tau.exe data/helloworld.lua
tau.exe data/hoverbike.lua
tau.exe data/md2.lua
tau.exe data/rotatingcube.lua
tau.exe data/specular.lua
pause
