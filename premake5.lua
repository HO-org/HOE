workspace "HOEngine"
    configurations { "Debug", "Release" }

project "HOEngine"
    kind "ConsoleApp"
    language "C++"
    targetdir "build/%{cfg.buildcfg}"

    includedirs { "include", "vendor/SDL2-2.0.20/x86_64-w64-mingw32/include/SDL2", "vendor/SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2" }
    includedirs { "src/**" }
    
    libdirs { "lib", "../lib", "vendor/SDL2-2.0.20/x86_64-w64-mingw32/lib", "vendor/SDL2_image-2.0.5/x86_64-w64-mingw32/lib" }

    links { "mingw32", "SDL2main", "SDL2", "SDL2_image" }
    
    files { "**.h", "**.cpp" }

    removefiles { "deprecated/**.h", "deprecated/**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"