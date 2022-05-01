# HOE - An amature game engine made by me
This is my first ever game engine!

It currently uses SDL, which it was migrated to from Raylib. It might be migrated again to OpenGL in the future.

It currently uses a component system that is a mix of composition and inheritance, composition is preferred but some components have a hierarchy.

It has a fixed-timestep game loop, and the non-fixed-update loop is currently unavailable due to issues with input, that might or might not be sorted out.

## Compiling
Currently the engine and game are a part of the same "project", and need to be compiled as one.

The project uses the Premake build system, and only uses cross-platform libraries and features, though it is currently only tested on Windows.
It should compile fine on Linux with a few tweaks, which is being worked on. MacOS is unknown as I have never used it.

## Compiling on Windows 10

### Requirements
MinGW-w64 ([Installation Instructions](https://github.com/hohfchns/HOE/blob/master/INSTALLMINGW64.md))

[git](https://git-scm.com/downloads)

### Compilation Process
Open a Powershell or Windows Terminal window in the directory you want the project to be stored in, for example ```C:\Dev\C++\```.

Enter the following commands:
``` bat
git clone --recursive https://github.com/hohfchns/HOE/
cd HOE
.\build.bat debug run
```
The first parameter for the build script is the debug or release mode.

The second parameter is optional and will start the game if included.

The game can also be launched from the executable ```HOEEngine.exe``` in the root project directory

The executable can be moved or shipped as long as the ```resources``` folder as well as the ```.dll``` files are in the same directory as it, otherwise the game will fail to run.
