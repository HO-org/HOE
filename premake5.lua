workspace "HOEngine"
    configurations { "Debug", "Release" }
    architecture "x86_64"

project "HOEngine"
    game_name = io.readfile("game_name.projname")
    game_dir = path.getrelative(".", io.readfile("game_dir.projdir"))
    game_folder = "%{game_dir}/" .. "%{game_name}"
    game_premake = string.format("%s/%s/premake5.lua", game_dir, game_name)

    kind "ConsoleApp"
    language "C++"
    targetdir "%{game_folder}"

    include(game_premake)

    -- include(game_dir .. "/" .. game_name .. "/premake5.lua")
    -- include(string.explode(game_premake, "\n")[0])
	
    -- libdirs { "lib", "../lib", "vendor/SDL2-2.0.20/x86_64-w64-mingw32/lib", "vendor/SDL2_image-2.0.5/x86_64-w64-mingw32/lib" }
    -- libdirs { "vendor/**" }
    
	filter "system:windows"
        -- SDL2 related includes
	    includedirs { "vendor/SDL2-2.0.20/x86_64-w64-mingw32/include/SDL2", "vendor/SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2" }
        -- Other includes
        includedirs { "vendor/loguru-2.1.0" }
	    
	    libdirs { "vendor/SDL2-2.0.20/x86_64-w64-mingw32/**", "vendor/SDL2_image-2.0.5/x86_64-w64-mingw32/**" }
        
        removelibdirs { "vendor/runtime/**" }

        links { "mingw32", "SDL2main", "SDL2", "SDL2_image" }
    	
    	targetname "%{game_name}"
	
	filter "system:linux"
        -- SDL2 related includes
		includedirs { "/usr/include/SDL2" }
        -- Other includes
        includedirs { "vendor/loguru-2.1.0" }
		
		libdirs { os.findlib("SDL2"), os.findlib("SDL2_image") }
		removelibdirs { "/**/lib32" }
    	
        links { "SDL2", "SDL2_image" }
    	
    	targetname "%{game_name}.game"
--		includedirs { "include/SDL2-linux" }
    filter {}

    includedirs { "src/**", "%{game_folder}" .. "/**" }
	
    files { "vendor/loguru-2.1.0/loguru.cpp" }
    files { "src/**.h", "src/**.cpp", "%{game_folder}" .. "/**.h", "%{game_folder}" .. "/**.cpp" }

    removefiles { "deprecated/**.h", "deprecated/**.cpp" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
