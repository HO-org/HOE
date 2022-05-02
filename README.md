# HOE - An amature game engine made by me
This is my first ever game engine!

It currently uses SDL, which it was migrated to from Raylib. It might be migrated again to OpenGL in the future.

It currently uses a component system that is a mix of composition and inheritance, composition is preferred but some components have a hierarchy.

It has a fixed-timestep game loop, and the non-fixed-update loop is currently unavailable due to issues with input, that might or might not be sorted out.

## Compiling
Currently the engine and game are a part of the same "project", and need to be compiled as one.

The project uses the Premake build system, and only uses cross-platform libraries and features, though it is currently only tested on Windows.
It should compile fine on Linux with a few tweaks, which is being worked on. MacOS is unknown as I have never used it.

---
#### The build script
The build script is functionally the same between Windows and Linux.

The first parameter is the release mode. It should be either ```debug``` or ```release```.

The second parameter ```run``` is optional and will start the game if included.

The game can also be launched from the executable ```HOEEngine.exe (Windows) / HOEngine.game (Linux)``` in the root project directory

The executable can be moved or shipped as long as the ```resources``` folder, and on Windows, the ```.dll``` files are also in the same directory as it, otherwise the game will fail to run.

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

## Compiling on Linux
### Install the dependencies ``git g++ sdl2 sdl2_image``
#### Command on Ubuntu (tested on 22.04)
``` bash
sudo apt install git g++ libsdl2-dev libsdl2-image-dev
```
#### Command on Arch / Arch based
``` bash
sudo pacman -Syu git sdl2 sdl2_image
```
If g++/gcc is not installed by default, use the command ```sudo pacman -Syu gcc```.
The libraries can also be found in the 3rd party Pamac GUI package manager, via native or AUR packages.

### Compilation Process
``` bash
git clone https://github.com/hohfchns/HOE
cd HOE
./build debug run
```
