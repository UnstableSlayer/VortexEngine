workspace "Vortex"
	platforms { "x86", "x64" }

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "VortexEngine/thirdParty/GLFW/include"
IncludeDir["Glad"] = "VortexEngine/thirdParty/Glad/include"
IncludeDir["ImGui"] = "VortexEngine/thirdParty/imgui"
IncludeDir["Glm"] = "VortexEngine/thirdParty/glm"

include "VortexEngine/thirdParty/GLFW"
include "VortexEngine/thirdParty/Glad"
include "VortexEngine/thirdParty/imgui"

project "VortexEngine"
	location "VortexEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "vpch.h"
	pchsource "VortexEngine/source/vpch.cpp"

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/source",
		"%{prj.name}/thirdParty/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.Glm}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"VE_PLATFORM_WINDOWS",
			"VE_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
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
			"VortexEngine/thirdParty/spdlog/include",
			"VortexEngine/AppHeaders"
		}

		links 
		{
			"VortexEngine"
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
			symbols "on"