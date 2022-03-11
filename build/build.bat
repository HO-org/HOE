if "%~1" == "run" ( del .\main.exe )
mingw32-make RAYLIB_BUILD_ARCH=x64 -j8
if "%~1" == "run" ( .\main.exe )