workspace "HOEngine"
    configurations { "Debug", "Release" }

project "HOEngine"
    kind "ConsoleApp"
    language "C++"
    targetdir "build/%{cfg.buildcfg}"

    includedirs { "include" }
    includedirs { "src/**" }
    
    libdirs { "lib", "../lib" }

    links { "raylib", "opengl32", "gdi32", "winmm" }
    
    files { "**.h", "**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"