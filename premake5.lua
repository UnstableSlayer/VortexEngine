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
	IncludeDir["Glad"] = "Vortex/thirdParty/Glad/include"
	IncludeDir["Glm"] = "Vortex/thirdParty/glm"
	IncludeDir["ImGui"] = "Vortex/thirdParty/imgui"
	IncludeDir["stb_image"] = "Vortex/thirdParty/stb_image"
    IncludeDir["spdlog"] = "Vortex/thirdParty/spdlog/include"
	IncludeDir["EnTT"] = "Vortex/thirdParty/Entt/include"
	IncludeDir["Assimp"] = "Vortex/thirdParty/Assimp"
	
    filter "system:linux"
        buildoptions {"-O2"}

	include "Vortex/thirdParty/Glad"
	include "Vortex/thirdParty/imgui"
	include "Vortex/thirdParty/Assimp"
	
	project "Vortex"
		location "Vortex"
		kind "StaticLib"
		language "C++"
		cppdialect "C++2a"
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
			"%{IncludeDir.spdlog}",
			"%{IncludeDir.SDL2}/include",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.Glm}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.EnTT}",
			"%{IncludeDir.stb_image}",
			"%{IncludeDir.Assimp}/include"
		}

		links
        {
				"Glad",
				"Assimp",
				"ImGui",
				"opengl32.lib",
				"SDL2"
        }
	
		filter "system:windows"
			systemversion "latest"
	
			defines
			{
				"VE_PLATFORM_WINDOWS",
			}

        filter "system:linux"
			systemversion "latest"
            buildoptions { "-fcoroutines" }

			defines
			{
				"VE_PLATFORM_LINUX"
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
		cppdialect "C++2a"
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
            "dl",
            "pthread",
			"Vortex",
			"Glad",
            "Assimp",
            "ImGui",
            "SDL2"
		}
		
		
		filter "system:windows"
			systemversion "latest"
	
			defines
			{
				"VE_PLATFORM_WINDOWS"
			}	

        filter "system:linux"
			systemversion "latest"
            buildoptions { "-fcoroutines" }

			defines
			{
				"VE_PLATFORM_LINUX"
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
		cppdialect "C++20"
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
            "dl",
            "pthread",
			"Vortex",
            "Glad",
            "Assimp",
            "ImGui",
            "SDL2"
		}
	
	
		filter "system:windows"
			systemversion "latest"
	
			defines
			{
				"VE_PLATFORM_WINDOWS"
			}	

        filter "system:linux"
			systemversion "latest"
            buildoptions { "-fcoroutines" }

			defines
			{
				"VE_PLATFORM_LINUX"
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
