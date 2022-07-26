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