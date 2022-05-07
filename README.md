# HOE - An amature game engine made by me
This is my first ever game engine!

It currently uses SDL, which it was migrated to from Raylib. It might be migrated again to OpenGL in the future.

It currently uses a component system that is a mix of composition and inheritance, composition is preferred but some components have a hierarchy.

It has a fixed-timestep game loop, and the non-fixed-update loop is currently unavailable due to issues with input, that might or might not be sorted out.

[The example game](https://github.com/hohfchns/HOETestGame)

## Compiling ##
Currently the engine and game are a part of the same "project", and need to be compiled as one.

The project uses the Premake build system, and only uses cross-platform libraries and features, though it is currently only tested on Windows.
It should compile fine on Linux with a few tweaks, which is being worked on. MacOS is unknown as I have never used it.

---
#### The project generator ####
The project generator script is written in python 3, and will setup a folder for your game project, and hook the engine to compile to it.
It will also create a Windows and Linux build script and copy the necessary files for your game to run.

The script is shared between Windows and Linux, with the only difference being the parameters given to it

---
#### The build script ####
The build script is functionally the same between Windows and Linux.

The only parameter is the release mode. It should be either ```debug``` or ```release```

The parameter can also be replaced with ```clean``` to clear the intermediate files and restart the compilation process. This can solve some problems with outdated files being compiled.

The executable can be moved or shipped as long as the ```resources``` folder, and on Windows, the ```.dll``` files are also in the same directory as it, otherwise the game will fail to run.

## Compiling on Windows 10 ##

### Requirements ###
MinGW-w64 ([Installation Instructions](https://github.com/hohfchns/HOE/blob/master/INSTALLMINGW64.md))

[git](https://git-scm.com/downloads)

[Python3](https://www.microsoft.com/en-us/p/python-310/9pjpw5ldxlz5#activetab=pivot:overviewtab)

### Compilation Process ###
Open a Powershell or Windows Terminal window in the directory you want the project to be stored in, for example ```C:\Dev\C++\```.

Enter the following commands:
``` bat
git clone --recursive https://github.com/hohfchns/HOE/
cd HOE
```
[Generate a project](#generating-a-project)

Open a Powershell or Windows Terminal in the directory of the project you generated, and run the command:
``` bat
.\build.bat debug
```
The project should now build, and you will see the ```{your_game_name}.exe``` file which you can now run!

## Compiling on Linux ##
### Install the dependencies ``git g++ sdl2 sdl2_image`` ###
#### Commands on Ubuntu (tested on 22.04)
``` bash
sudo apt update
sudo apt install make git g++ libsdl2-dev libsdl2-image-dev
```
#### Command on Arch / Arch based
``` bash
sudo pacman -Syu make gcc git sdl2 sdl2_image
```
The libraries can also be found in the 3rd party Pamac GUI package manager, via native or AUR packages.

### Compilation Process ###
``` bash
git clone --recursive https://github.com/hohfchns/HOE
cd HOE
```
[Generate a project](#generating-a-project)

Open a terminal in the directory of the project you generated, and run the command:
``` bash
./build debug
```

The project should now build, and you will see the ```{your_game_name}.game``` file which you can now run!

## Generating a project ###
#### Guided installation
To generate a project with the guided generator, run the command:
``` bash
python3 configure_project.py
```
An example of what you might see:
```
Enter the parent directory... : C:\Dev\HOE-Games\
Enter the name for the project: MyHOEGame
```
#### Using arguments
The generator can also take both dialogs as arguments
``` bash
python3 configure_project.py PARENT_DIR PROJECT_NAME
```
### The parameters
The first parameter should be the parent directory of the desired project directory.

For example, for the project folder to be ```C:\Dev\HOE-Development\AnHOEGame``` give the parameter ```C:\Dev\HOE-Development\```.

**It is important that you add the final ```\``` or ```/``` at the end, or else the project will be in the wrong directory**

The second parameter should be the name of the project or game. For example ```AnHOEGame```.


## Multiple projects ##
Currently to have multiple projects, you would have to clone the engine again under a different directory/name
