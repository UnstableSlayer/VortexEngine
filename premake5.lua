workspace "Vortex"
	platforms { "x86", "x64" }
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		"%{prj.name}/thirdParty/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"VE_PLATFORM_WINDOWS",
			"VE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/GameProject")
		}

	filter "configurations:Debug"
		defines "VE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "VE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "VE_DIST"
		symbols "On"

	filter{ "system:windows", "configurations:Release" }
		buildoptions "/MT"


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
			symbols "On"

		filter "configurations:Release"
			defines "VE_RELEASE"
			optimize "On"

		filter "configurations:Dist"
			defines "VE_DIST"
			symbols "On"

		filter{ "system:windows", "configurations:Release" }
			buildoptions "/MT"