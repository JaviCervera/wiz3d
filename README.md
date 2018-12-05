# Micron
Micron is a minimalist game engine licensed under the Zlib license. Its main features are:

* Lua scripting
* OpenGL fixed pipeline graphics.
* GLFW for window and input management.
* OpenAL for audio.

The core runtime has been written in pure C, with the goal of being easily portable to any platform. It has currently been tested on Windows, macOS and Linux.

Since Micron uses submodules, to correctly clone the repository, do:

`git clone --recursive https://github.com/JaviCervera/micron.git`

If you have already cloned the repository without initializing submodules, you can do it afterwards running this on the Micron repository:

`git submodule update --init`

To pull changes from the repository, including its submodules, do:

`git pull --recurse-submodules`

## Building on Windows
The libraries have been compiled with TDM-GCC. This compiler suite has not been updated in a while, but it can compile Micron without issues.

You should have **Cmake** installed and added to your PATH to build the engine. In order to compile, just double click the `build.bat` file. The executable file `micron.exe` will be created on the `_build` folder. All the samples will run automatically when you run the build script.

## Building on macOS
You should have **Cmake** and **swig3.0** installed to be able to build the engine. You can install them for example with [Brew](https://brew.sh/). After installing Brew on your system, type:

`$brew install cmake`
`$brew install swig3.0`

Then, just double click from Finder on `build.command` and the executable file `micron` will be created on the `_build` folder (it is a 32 bit binary). All the samples will run automatically when you run the build script.

## Building on Linux
You should have **Cmake** and **swig3.0** installed to be able to build the engine. For example, to install them on Ubuntu, type:

`$sudo apt install cmake`

`$sudo apt install swig3.0`

Then, from a Terminal go to the Micron folder and run the build script:

`$./build.sh`

The executable file `micron` will be created on the `_build` folder (it is a 64 bit binary). All the samples will run automatically when you run the build script.

## Using Micron
The runtime accepts one optional parameter with the name of the Lua script to run. If you don't provide the parameter, then the file `data/main.lua` will be run.

The script folder is always set as the active directory when running a program, so all paths should be relative to this folder.

## TODO v1.0
- [x] Replace SDL with GLFW
- [x] Add collisions
- [ ] Add static collisions
- [ ] Add 2d functions
- [ ] Add OpenAL audio support (wav and ogg)
- [ ] Port Vortex samples

## TODO v1.0.x
- [ ] Add object.newfrommemory()
- [ ] Add ini support
- [ ] Add file manager with pak support
- [ ] Add spot lights
- [ ] Add more primitives (sphere, cone, cylinder, ramp)
- [ ] Add material.ambient?
- [ ] Add TinyGL support
- [ ] Add UI library (https://github.com/vurtun/nuklear)

## TODO v1.1
- [ ] Add micron_config.h
- [ ] Add Doom wad support (maps included)

## TODO v1.2
- [ ] Add lightmaps
- [ ] Add texture wal support
- [ ] Add Quake2 bsp support
