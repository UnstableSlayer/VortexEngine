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
	IncludeDir["Glad"] = "Vortex/thirdParty/glad/include"
	IncludeDir["Glm"] = "Vortex/thirdParty/glm"
	IncludeDir["ImGui"] = "Vortex/thirdParty/imgui"
	IncludeDir["stb_image"] = "Vortex/thirdParty/stb_image"
    IncludeDir["spdlog"] = "Vortex/thirdParty/spdlog/include"
	IncludeDir["EnTT"] = "Vortex/thirdParty/Entt/include"
	IncludeDir["Assimp"] = "Vortex/thirdParty/Assimp"
	
    filter "system:linux"
        buildoptions {"-O2"}

	include "Vortex/thirdParty/glad"
	include "Vortex/thirdParty/imgui"
	include "Vortex/thirdParty/Assimp"
	include "Vortex"
	include "GameProject"
	include "VortexEditor"