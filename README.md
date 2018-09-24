# Tau
Tau is a minimalist game engine licensed under the Zlib license. Its main features are:

* Lua scripting
* OpenGL fixed pipeline graphics.
* SDL for window, input and sound management.

The core runtime has been written in pure C, with the goal of being easily portable to any platform. It has currently been tested on Windows, macOS and Linux.

## Building on Windows
The libraries have been compiled with TDM-GCC. This compiler suite has not been updated in a while, but it can compile Tau without issues.

You should have **Cmake** installed and added to your PATH to build the engine. In order to compile, just double click the `build.bat` file. The executable file `tau.exe` will be created on the `_build` folder. All the samples will run automatically when you run the build script.

## Building on macOS
You should have **Cmake** and **swig3.0** installed to be able to build the engine. You can install them for example with [Brew](https://brew.sh/). After installing Brew on your system, type:

`$brew install cmake`
`$brew install swig3.0`

Then, just double click from Finder on `build.command` and the executable file `tau` will be created on the `_build` folder (it is a 32 bit binary). All the samples will run automatically when you run the build script.

## Building on Linux
You should have **Cmake** and **swig3.0** installed to be able to build the engine. For example, to install them on Ubuntu, type:

`$sudo apt install cmake`

`$sudo apt install swig3.0`

Then, from a Terminal go to the Tau folder and run the build script:

`$./build.sh`

The executable file `tau` will be created on the `_build` folder (it is a 64 bit binary). All the samples will run automatically when you run the build script.

## Using Tau
The runtime accepts one optional parameter with the name of the Lua script to run. If you don't provide the parameter, then the file `data/main.lua` will be run.

The script folder is always set as the active directory when running a program, so all paths should be relative to this folder.
