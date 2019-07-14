#!/bin/sh
cd `dirname $0`

echo "copying beam lib..."
cp _build/libbeam.dylib examples/libbeam.dylib

echo "building examples..."
cd examples
gcc -o angel angel.c -L. -lbeam
gcc -o billboards billboards.c -L. -lbeam
gcc -o collisions collisions.c -L. -lbeam
gcc -o fog fog.c -L. -lbeam
gcc -o helloworld helloworld.c -L. -lbeam
gcc -o hoverbike hoverbike.c -L. -lbeam
gcc -o md2 md2.c -L. -lbeam
gcc -o primitives primitives.c -L. -lbeam
gcc -o rotatingcube rotatingcube.c -L. -lbeam
gcc -o specular specular.c -L. -lbeam

echo "running examples..."
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
rm libbeam.dylib
cd ..
