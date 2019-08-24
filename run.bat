@echo off

echo copying spark dll...
copy "_build\libspark.dll" examples

echo building examples...
cd examples
gcc -o 1-helloworld.exe 1-helloworld.c -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows
gcc -o 2-primitives.exe 2-primitives.c -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows
gcc -o 3-texture2d.exe 3-texture2d.c -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows
gcc -o 4-triangle.exe 4-triangle.c -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows
gcc -o 5-lightmap.exe 5-lightmap.c -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows
gcc -o 6-billboards.exe 6-billboards.c -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows
gcc -o 7-lighting.exe 7-lighting.c -L. -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows
gcc -o 8-fog.exe 8-fog.c -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows
gcc -o 9-collisions.exe 9-collisions.c -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows
gcc -o 10-specular.exe 10-specular.c -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows
gcc -o 11-md2.exe 11-md2.c -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows
gcc -o 12-angel.exe 12-angel.c -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows
gcc -o 13-hoverbike.exe 13-hoverbike.c -DDLL_IMPORT -DPLATFORM_GLFW -L../_CMAKE -lspark.dll -mwindows

echo running examples...
1-helloworld.exe
2-primitives.exe
3-texture2d.exe
4-triangle.exe
5-lightmap.exe
6-billboards.exe
7-lighting.exe
8-fog.exe
9-collisions.exe
10-specular.exe
11-md2.exe
12-angel.exe
13-hoverbike.exe

echo cleaning up...
del 1-helloworld.exe
del 2-primitives.exe
del 3-texture2d.exe
del 4-triangle.exe
del 5-lightmap.exe
del 6-billboards.exe
del 7-lighting.exe
del 8-fog.exe
del 9-collisions.exe
del 10-specular.exe
del 11-md2.exe
del 12-angel.exe
del 13-hoverbike.exe
del libspark.dll
cd ..

pause
