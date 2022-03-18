mingw32-make RAYLIB_BUILD_ARCH=x64 -j8 config="%~1"
if "%~2" == "run" ( .\build\Debug\HOEngine.exe )