# How to install MinGW-w64 on Windows 10
## Using MSYS2 (recommended)
[Follow the instructions on the MSYS2 page](https://www.msys2.org/)

Add the mingw64 installation in your MSYS2 install directory to your PATH, [as described below](https://github.com/HO-org/HOE/edit/master/INSTALLMINGW64.md#adding-directoryfolder-to-path)
## Downloading manually
* [Go to the SourceForge page](https://sourceforge.net/projects/mingw-w64/files/).
* Scroll down a bit and download version 8 with the required parameters for your OS, usually ```x86_64-win32-seh```. As of May 1st, 2022, do not use the installer, as it does not work!
* Extract the zip file from the download
* Go into the folder, and copy the ```mingw64``` folder to the desired location to store the library, recommended is ```C:\mingw64```.
* Add the ```{LIBRARY_LOCATION}\mingw64\bin``` folder to your ```PATH``` environment variable ([described below](https://github.com/HO-org/HOE/edit/master/INSTALLMINGW64.md#adding-directoryfolder-to-path)).

## Adding directory/folder to PATH ##
* Open the start menu.
* Search for ```environment```.
* Click the result that says ```Edit the system environment variables```.
* In the newly opened window, press the ```Environment Variables...``` button.
* Under ```System variables```, locate the ```Path``` entry.
* Click it, then click the ```Edit``` button at the bottom.
* Click the ```New``` button on the right, then click the ```Browse...``` button on the right.
* Navigate to the folder where you put ```mingw64``` and select the ```bin``` folder inside of it.
* Click ```Ok```.
* Restart your computer.
