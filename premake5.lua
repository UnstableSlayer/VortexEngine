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

include "VortexEngine/thirdParty/GLFW"
include "VortexEngine/thirdParty/Glad"

project "VortexEngine"
	location "VortexEngine"
	kind "SharedLib"
	language "C++"

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
		"%{IncludeDir.Glad}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"VE_PLATFORM_WINDOWS",
			"VE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/GameProject")
		}

	filter "configurations:Debug"
		defines "VE_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "VE_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "VE_DIST"
		buildoptions "/MD"
		symbols "On"

	project "GameProject"
		location "GameProject"
		kind "ConsoleApp"
		language "C++"

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
			cppdialect "C++17"
			staticruntime "On"
			systemversion "latest"

			defines
			{
				"VE_PLATFORM_WINDOWS"
			}

		filter "configurations:Debug"
			defines "VE_DEBUG"
			buildoptions "/MDd"
			symbols "On"

		filter "configurations:Release"
			defines "VE_RELEASE"
			buildoptions "/MD"
			optimize "On"

		filter "configurations:Dist"
			defines "VE_DIST"
			buildoptions "/MD"
			symbols "On"

		filter{ "system:windows", "configurations:Release" }
			buildoptions "/MT"