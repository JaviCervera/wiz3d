#!/bin/sh
cd `dirname $0`

echo "building examples..."
cd examples
gcc -o 1-helloworld 1-helloworld.c -L../_build -lbeam
gcc -o 2-primitives 2-primitives.c -L../_build -lbeam
gcc -o 3-texture2d 3-texture2d.c -L../_build -lbeam
gcc -o 4-triangle 4-triangle.c -L../_build -lbeam
gcc -o 5-rotatingcube 5-rotatingcube.c -L../_build -lbeam
gcc -o 6-billboards 6-billboards.c -L../_build -lbeam
gcc -o 7-lighting 7-lighting.c -L../_build -lbeam
gcc -o 8-fog 8-fog.c -L../_build -lbeam
gcc -o 9-collisions 9-collisions.c -L../_build -lbeam
gcc -o 10-specular 10-specular.c -L../_build -lbeam
gcc -o 11-md2 11-md2.c -L../_build -lbeam
gcc -o 12-angel 12-angel.c -L../_build -lbeam -lm
gcc -o 13-hoverbike 13-hoverbike.c -L../_build -lbeam

echo "running examples..."
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../_build
export LD_LIBRARY_PATH
./1-helloworld
./2-primitives
./3-texture2d
./4-triangle
./5-rotatingcube
./6-billboards
./7-lighting
./8-fog
./9-collisions
./10-specular
./11-md2
./12-angel
./13-hoverbike

echo "cleaning up..."
rm 1-helloworld
rm 2-primitives
rm 3-texture2d
rm 4-triangle
rm 5-rotatingcube
rm 6-billboards
rm 7-lighting
rm 8-fog
rm 9-collisions
rm 10-specular
rm 11-md2
rm 12-angel
rm 13-hoverbike
cd ..
