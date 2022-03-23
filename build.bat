del .\build\Debug\HOEngine.exe
del .\HOEngine.exe

premake5 gmake2
mingw32-make RAYLIB_BUILD_ARCH=x64 -j8 config="%~1"

copy .\build\"%~1"\HOEngine.exe .\

if "%~2" == "run" ( .\HOEngine.exe )