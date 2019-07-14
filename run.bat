@echo off

echo copying beam dll...
copy "_build\libbeam.dll" examples

echo building examples...
cd examples
gcc -o angel.exe angel.c -DDLL_IMPORT -L../_CMAKE -lbeam.dll -mwindows
gcc -o billboards.exe billboards.c -DDLL_IMPORT -L../_CMAKE -lbeam.dll -mwindows
gcc -o collisions.exe collisions.c -DDLL_IMPORT -L../_CMAKE -lbeam.dll -mwindows
gcc -o fog.exe fog.c -DDLL_IMPORT -L../_CMAKE -lbeam.dll -mwindows
gcc -o helloworld.exe helloworld.c -DDLL_IMPORT -L../_CMAKE -lbeam.dll -mwindows
gcc -o hoverbike.exe hoverbike.c -DDLL_IMPORT -L../_CMAKE -lbeam.dll -mwindows
gcc -o md2.exe md2.c -DDLL_IMPORT -L../_CMAKE -lbeam.dll -mwindows
gcc -o primitives.exe primitives.c -DDLL_IMPORT -L../_CMAKE -lbeam.dll -mwindows
gcc -o rotatingcube.exe rotatingcube.c -DDLL_IMPORT -L../_CMAKE -lbeam.dll -mwindows
gcc -o specular.exe specular.c -DDLL_IMPORT -L../_CMAKE -lbeam.dll -mwindows

echo running examples...
angel.exe
billboards.exe
collisions.exe
fog.exe
helloworld.exe
hoverbike.exe
md2.exe
primitives.exe
rotatingcube.exe
specular.exe

echo cleaning up...
del angel.exe
del billboards.exe
del collisions.exe
del fog.exe
del helloworld.exe
del hoverbike.exe
del md2.exe
del primitives.exe
del rotatingcube.exe
del specular.exe
del libbeam.dll
cd ..

pause
