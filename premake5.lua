workspace "VortexEngine"
	platforms { "x86", "x64", "arm", "arm64"}
	startproject "GameProject"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	IncludeDir = {}
	IncludeDir["SDL2"] = "Vortex/thirdParty/SDL2"
	IncludeDir["Glad"] = "Vortex/thirdParty/Glad/include"
	IncludeDir["Glm"] = "Vortex/thirdParty/glm"
	IncludeDir["stb_image"] = "Vortex/thirdParty/stb_image"
	IncludeDir["EnTT"] = "Vortex/thirdParty/Entt/include"
	IncludeDir["Assimp"] = "Vortex/thirdParty/Assimp"
	
	include "Vortex/thirdParty/Glad"
	include "Vortex/thirdParty/Assimp"
	
	project "Vortex"
		location "Vortex"
		kind "StaticLib"
		language "C++"
		cppdialect "C++20"
		staticruntime "on"
	
		targetdir ("bin/" .. outputDir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
		pchheader "vpch.h"
		pchsource "Vortex/source/vpch.cpp"
	
		files
		{
			"%{prj.name}/source/**.h",
			"%{prj.name}/source/**.cpp",
			"%{prj.name}/thirdParty/stb_image/**.h",
			"%{prj.name}/thirdParty/stb_image/**.cpp",
			"%{prj.name}/thirdParty/glm/glm/**.hpp",
			"%{prj.name}/thirdParty/glm/glm/**.inl"
		}

		defines
		{
			"_CRT_SECURE_NO_WARNINGS"
		}

		includedirs
		{
			"%{prj.name}/source",
			"%{prj.name}/thirdParty/spdlog/include",
			"%{IncludeDir.SDL2}/include",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.Glm}",
			"%{IncludeDir.EnTT}",
			"%{IncludeDir.stb_image}",
			"%{IncludeDir.Assimp}/include"
		}
		
		linkoptions { "/NODEFAULTLIB", "/FORCE:MULTIPLE"}
		
		filter "configurations:Debug"
			libdirs
			{
				"%{IncludeDir.SDL2}/lib/%{cfg.architecture}/Debug"
			}
			
			links
			{
				"libucrtd",
				"libvcruntimed",
				"libcpmtd",
				"libcmtd",
			
				"Glad",
				"Assimp",
				"opengl32.lib",
				
				"winmm.lib",
				"imm32.lib",
				"version.lib",
				"setupapi.lib",
				"SDL2",
				"SDL2main"
			}
		filter "configurations:Release or Dist"
			libdirs
			{
				"%{IncludeDir.SDL2}/lib/%{cfg.architecture}/Release"
			}
			links
			{
				"libucrt",
				"libvcruntime",
				"libcpmt",
				"libcmt",
			
				"Glad",
				"Assimp",
				"opengl32.lib",
				
				"winmm.lib",
				"imm32.lib",
				"version.lib",
				"setupapi.lib",
				"SDL2",
				"SDL2main"
			}
	
		filter "system:windows"
			systemversion "latest"
	
			defines
			{
				"VE_PLATFORM_WINDOWS",
			}
	
	
		filter "configurations:Debug"
			defines "VE_DEBUG"
			runtime "Debug"
			symbols "on"
	
		filter "configurations:Release"
			defines "VE_RELEASE"
			runtime "Release"
			optimize "on"
	
		filter "configurations:Dist"
			defines "VE_DIST"
			runtime "Release"
			optimize "on"
	
	
	
	project "GameProject"
		location "GameProject"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++20"
		staticruntime "on"
	
		targetdir ("bin\\" .. outputDir .. "\\%{prj.name}")
		objdir ("bin-int\\" .. outputDir .. "\\%{prj.name}")
	
		files
		{
			"%{prj.name}/source/**.h",
			"%{prj.name}/source/**.cpp"
		}
	
		includedirs
		{
			"Vortex/thirdParty/spdlog/include",
			"Vortex/source",
			"%{IncludeDir.Glm}",
			"%{IncludeDir.EnTT}"
		}
		
		linkoptions { "/NODEFAULTLIB", "/FORCE:MULTIPLE"}

		links 
		{
			"Vortex"
		}
		
		
		filter "system:windows"
			systemversion "latest"
	
			defines
			{
				"VE_PLATFORM_WINDOWS"
			}	
	
		filter "configurations:Debug"
			defines "VE_DEBUG"
			runtime "Debug"
			symbols "on"
	
		filter "configurations:Release"
			defines "VE_RELEASE"
			runtime "Release"
			optimize "on"
	
		filter "configurations:Dist"
			defines "VE_DIST"
			runtime "Release"
			optimize "on"



	project "VortexEditor"
		location "VortexEditor"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"
	
		targetdir ("bin/" .. outputDir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputDir .. "/%{prj.name}")
	
		files
		{
			"%{prj.name}/source/**.h",
			"%{prj.name}/source/**.cpp"
		}
	
		includedirs
		{
			"Vortex/thirdParty/spdlog/include",
			"Vortex/source",
			"%{IncludeDir.Glm}",
			"%{IncludeDir.EnTT}"
		}
	
		links 
		{
			"Vortex"
		}
	
	
		filter "system:windows"
			systemversion "latest"
	
			defines
			{
				"VE_PLATFORM_WINDOWS"
			}	
	
		filter "configurations:Debug"
			defines "VE_DEBUG"
			runtime "Debug"
			symbols "on"
	
		filter "configurations:Release"
			defines "VE_RELEASE"
			runtime "Release"
			optimize "on"
	
		filter "configurations:Dist"
			defines "VE_DIST"
			runtime "Release"
			optimize "on"