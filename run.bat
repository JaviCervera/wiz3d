@echo off

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
