del .\HOEngine.exe

.\vendor\premake5\premake5.exe gmake2
mingw32-make RAYLIB_BUILD_ARCH=x64 -j8 config="%~1"

if "%~2" == "run" ( .\HOEngine.exe )