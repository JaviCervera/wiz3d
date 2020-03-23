#!/bin/sh
cd `dirname $0`

echo "copying wiz3d lib..."
cp _build/libwiz3d.dylib examples/libwiz3d.dylib

echo "building examples..."
cd examples
gcc -o 1-helloworld 1-helloworld.c -DPLATFORM_GLFW -L. -lwiz3d
gcc -o 2-primitives 2-primitives.c -DPLATFORM_GLFW -L. -lwiz3d
gcc -o 3-texture2d 3-texture2d.c -DPLATFORM_GLFW -L. -lwiz3d
gcc -o 4-triangle 4-triangle.c -DPLATFORM_GLFW -L. -lwiz3d
gcc -o 5-lightmap 5-lightmap.c -DPLATFORM_GLFW -L. -lwiz3d
gcc -o 6-billboards 6-billboards.c -DPLATFORM_GLFW -L. -lwiz3d
gcc -o 7-lighting 7-lighting.c -DPLATFORM_GLFW -L. -lwiz3d
gcc -o 8-fog 8-fog.c -DPLATFORM_GLFW -L. -lwiz3d
gcc -o 9-collisions 9-collisions.c -DPLATFORM_GLFW -L. -lwiz3d
gcc -o 10-specular 10-specular.c -DPLATFORM_GLFW -L. -lwiz3d
gcc -o 11-md2 11-md2.c -DPLATFORM_GLFW -L. -lwiz3d
gcc -o 12-angel 12-angel.c -DPLATFORM_GLFW -L. -lwiz3d
gcc -o 13-hoverbike 13-hoverbike.c -DPLATFORM_GLFW -L. -lwiz3d

echo "running examples..."
./1-helloworld
./2-primitives
./3-texture2d
./4-triangle
./5-lightmap
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
rm 5-lightmap
rm 6-billboards
rm 7-lighting
rm 8-fog
rm 9-collisions
rm 10-specular
rm 11-md2
rm 12-angel
rm 13-hoverbike
rm libwiz3d.dylib
cd ..
