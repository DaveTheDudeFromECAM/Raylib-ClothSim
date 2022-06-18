newoption 
{
   trigger = "opengl43",
   description = "use OpenGL 4.3"
}

workspace "App"
	configurations { "Debug","Debug.DLL", "Release", "Release.DLL" }
	platforms { "x64"}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		
	filter "configurations:Debug.DLL"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"	
		
	filter "configurations:Release.DLL"
		defines { "NDEBUG" }
		optimize "On"	
		
	filter { "platforms:x64" }
		architecture "x86_64"
		
	targetdir "build/bin/%{cfg.buildcfg}/"
	
	defines{"PLATFORM_DESKTOP"}
	if (_OPTIONS["opengl43"]) then
		defines{"GRAPHICS_API_OPENGL_43"}
	else
		defines{"GRAPHICS_API_OPENGL_33"}
	end
	
project "raylib"
		filter "configurations:Debug.DLL OR Release.DLL"
			kind "SharedLib"
			defines {"BUILD_LIBTYPE_SHARED"}
			
		filter "configurations:Debug OR Release"
			kind "StaticLib"
			
		filter "action:vs*"
			defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
			links {"winmm"}
			
		filter "action:gmake*"
			links {"pthread", "GL", "m", "dl", "rt", "X11"}
			
		filter{}
		
		location "build/raylib"
		language "C++"
		targetdir "build/bin/%{cfg.buildcfg}"
		cppdialect "C++17"
		
		includedirs { "raylib/src", "raylib/src/external/glfw/include"}
		vpaths 
		{
			["Header Files"] = { "raylib/src/**.h"},
			["Source Files/*"] = {"raylib/src/**.c"},
		}
		files {"raylib/src/*.h", "raylib/src/*.c"}
		
project "App"
	kind "ConsoleApp"
	location "build/%{wks.name}"
	language "C++"
	targetdir "build/bin/%{cfg.buildcfg}"
	cppdialect "C++17"
	debugdir "."
	
	includedirs {"src", "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.5\\include"} --locate the header file CL.h and its folder
	vpaths 
	{
		["Header Files"] = { "**.h"},
		["Source Files"] = {"**.c", "**.cpp"},
	}
	files {"**.c", "**.cpp", "**.h"}
	removefiles {"raylib/**"}

	links {"raylib"}
	
	includedirs { "raylib/src" }
	defines{"PLATFORM_DESKTOP", "GRAPHICS_API_OPENGL_33"}
	
	filter "action:vs*"
		defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
		dependson {"raylib"}
		links {"raylib.lib", "winmm", "kernel32", "OpenCL"}
		libdirs {"build/bin/%{cfg.buildcfg}", "C:\\Program Files\\NVIDIA GPU Computing Toolkit\\CUDA\\v11.5\\lib\\x64"}  --locate the OpenCL.lib file
		
	filter "action:gmake*"
		links {"pthread", "GL", "m", "dl", "rt", "X11"}