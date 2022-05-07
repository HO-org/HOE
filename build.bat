.\vendor\premake5\premake5.exe gmake2
if "%~1" == "clean" (mingw32-make clean)
if not "%~1" == "clean" (mingw32-make -j8 config="%~1")
