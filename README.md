# Beam

Beam is a minimalist game engine licensed under the Zlib license. Its main features are:

* Simple procedural API written in C.
* OpenGL fixed pipeline graphics.
* Allegro, GLFW/OpenAL or SDL2 for window, input and audio management.

It has the goal of being easily portable to any platform. It has currently been tested on Windows, macOS and Linux.

## Building

### Windows

You should have **Cmake** installed and added to your `PATH` to build the engine. In order to compile, just double click the `build.bat` file. The library `libbeam.dll` will be created on the `_build` folder.

Once built, you can drastically reduce the size of the generated `libbeam.dll` library by running `compress.exe`, which will use the UPX compressor.

To run the examples, use the `run.bat` script. You must have previously built the engine.

### macOS

You should have **Cmake** installed to be able to build the engine. You can install it for example with [Brew](https://brew.sh/). After installing Brew on your system, type:

`$brew install cmake`

Then, just double click from Finder on `build.command` and the library file `libbeam.dylib` will be created on the `_build` folder.

To run the examples, use the `run.command` script. You must have previously built the engine.

### Linux

You should have **Cmake** installed to be able to build the engine. For example, to install it on Ubuntu, type:

`$sudo apt install cmake`

Then, from a Terminal go to the Beam folder and run the build script:

`$./build.sh`

The library file `libbeam.so` will be created on the `_build` folder (it is a 64 bit binary).

To run the examples, use the `run.sh` script. You must have previously built the engine.

## Documentation

See [here](./doc/documentation.md).

## Roadmap

### v0.9-beta

- [x] Replace structs with functions for everything.
- [x] Mipmapping and lightmaps.
- [x] Fix object shininess.
- [x] Replace light range with attenuation.
- [ ] Cube mapping.
- [ ] Other features from ColdSteel, Soil and Wiz3D?
- [ ] material.ambient.
- [ ] Spot lights.
- [ ] Audio with support for wav and ogg formats (OpenAL only by now).
- [ ] More Vortex examples.

### v1.0

- [ ] Modern pipeline support, with the ability to use custom shaders, and normal, light, emissive, specular, ambient and cubic textures.
- [ ] Cache resources when loading.
- [ ] More DrawTexture options.
- [ ] Add billboard animation support.
- [ ] Ini file support.
- [ ] More primitives (sphere, cone, cylinder, wedge).
- [ ] Emscripten support.

### v1.1

- [ ] UI library (https://github.com/vurtun/nuklear).
- [ ] PCX texture support.
- [ ] Bitmap font support.
- [ ] TinyGL or Klimt support (with fixed point math).

### v2.0

- [ ] Vulkan renderer.
- [ ] Skeletal animation.
- [ ] Physically Based Rendering.

### Other

- [ ] Doom WAD support (including maps), so maps can be created with [Doom Builder](http://doombuilder.com/).
- [ ] Quake2 BSP and WAL texture support, so maps can be created with [TrenchBroom](http://www.kristianduske.com/trenchbroom/).
