workspace "HOEngine"
    configurations { "Debug", "Release" }
    architecture "x86_64"

project "HOEngine"
    kind "ConsoleApp"
    language "C++"
    targetdir "."
	
    -- libdirs { "lib", "../lib", "vendor/SDL2-2.0.20/x86_64-w64-mingw32/lib", "vendor/SDL2_image-2.0.5/x86_64-w64-mingw32/lib" }
    -- libdirs { "vendor/**" }
    
	filter "system:windows"
	    includedirs { "include", "vendor/SDL2-2.0.20/x86_64-w64-mingw32/include/SDL2", "vendor/SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2" }
	    
	    libdirs { "vendor/SDL2-2.0.20/x86_64-w64-mingw32/**", "vendor/SDL2_image-2.0.5/x86_64-w64-mingw32/**" }
    	links { "mingw32", "SDL2main", "SDL2", "SDL2_image" }
    	
    	targetname "HOEngine.exe"
	
	filter "system:linux"
		includedirs { "/usr/include/SDL2" }
		
		libdirs { os.findlib("SDL2"), os.findlib("SDL2_image") }
		removelibdirs { "/**/lib32" } 
    	links { "SDL2", "SDL2_image" }
    	
    	targetname "HOEngine.game"
--		includedirs { "include/SDL2-linux" }
	
    includedirs { "src/**" }
	
    files { "src/**.h", "src/**.cpp" }

    removefiles { "deprecated/**.h", "deprecated/**.cpp", "vendor/loguru-2.1.0/**" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
