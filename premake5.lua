workspace "VortexEngine"
	platforms { "x86", "x64" }
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
	IncludeDir["GLFW"] = "Vortex/thirdParty/GLFW/include"
	IncludeDir["Glad"] = "Vortex/thirdParty/Glad/include"
	IncludeDir["ImGui"] = "Vortex/thirdParty/imgui"
	IncludeDir["Glm"] = "Vortex/thirdParty/glm"
	IncludeDir["stb_image"] = "Vortex/thirdParty/stb_image"
	IncludeDir["EnTT"] = "Vortex/thirdParty/Entt/include"
	IncludeDir["Assimp"] = "Vortex/thirdParty/Assimp"
	
	include "Vortex/thirdParty/GLFW"
	include "Vortex/thirdParty/Glad"
	include "Vortex/thirdParty/imgui"
	include "Vortex/thirdParty/Assimp"
	
	project "Vortex"
		location "Vortex"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
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
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.Glm}",
			"%{IncludeDir.EnTT}",
			"%{IncludeDir.stb_image}",
			"%{IncludeDir.Assimp}/include"
		}
		
		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"Assimp",
			"opengl32.lib",
		}
		
		
	
		filter "system:windows"
			systemversion "latest"
	
			defines
			{
				"VE_PLATFORM_WINDOWS",
				"VE_BUILD_DLL",
				"GLFW_INCLUDE_NONE",
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
			"Vortex",
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