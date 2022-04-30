del .\HOEngine.exe

.\vendor\premake5\premake5.exe gmake2
mingw32-make -j8 config="%~1"

if "%~2" == "run" ( .\HOEngine.exe )