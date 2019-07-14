#!/bin/sh
cd `dirname $0`

echo "building examples..."
cd examples
gcc -o angel angel.c -L../_build -lm -lbeam
gcc -o billboards billboards.c -L../_build -lbeam
gcc -o collisions collisions.c -L../_build -lbeam
gcc -o fog fog.c -L../_build -lbeam
gcc -o helloworld helloworld.c -L../_build -lbeam
gcc -o hoverbike hoverbike.c -L../_build -lbeam
gcc -o md2 md2.c -L../_build -lbeam
gcc -o primitives primitives.c -L../_build -lbeam
gcc -o rotatingcube rotatingcube.c -L../_build -lbeam
gcc -o specular specular.c -L../_build -lbeam

echo "running examples..."
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../_build
export LD_LIBRARY_PATH
./angel
./billboards
./collisions
./fog
./helloworld
./hoverbike
./md2
./primitives
./rotatingcube
./specular

echo "cleaning up..."
rm angel
rm billboards
rm collisions
rm fog
rm helloworld
rm hoverbike
rm md2
rm primitives
rm rotatingcube
rm specular
cd ..
