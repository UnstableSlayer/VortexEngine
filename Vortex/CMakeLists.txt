# vulkan
enable_language(CXX)
find_package(Vulkan REQUIRED)

# SDL2
add_subdirectory(thirdParty/SDL2)

# imgui
enable_language(CXX)

set(IMGUI_SRCS
        thirdParty/imgui/imconfig.h
		thirdParty/imgui/imgui.h
		thirdParty/imgui/imgui.cpp
		thirdParty/imgui/imgui_draw.cpp
		thirdParty/imgui/imgui_internal.h
		thirdParty/imgui/imgui_widgets.cpp
		thirdParty/imgui/imstb_rectpack.h
		thirdParty/imgui/imstb_textedit.h
		thirdParty/imgui/imstb_truetype.h
		thirdParty/imgui/imgui_demo.cpp
		thirdParty/imgui/imgui_tables.cpp
)

add_library(imgui STATIC ${IMGUI_SRCS})

# assimp
set(BUILD_SHARED_LIBS OFF)
set(ASSIMP_DOUBLE_PRECISION ON)
set(ASSIMP_BUILD_TESTS OFF)
set(INJECT_DEBUG_POSTFIX ON)
set(ASSIMP_INSTALL_PDB ON)

add_definitions(-D__GLIBCXX_TYPE_INT_N_0=__int128)
add_definitions(-D__GLIBCXX_BITSIZE_INT_N_0=128)

add_subdirectory(thirdParty/assimp)
#############

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#add_compile_options(-Wunused-result -Wint-to-pointer-cast -Wswitch)

if(CMAKE_C_COMPILER_ID EQUAL GNU)
    add_compile_options(-fcoroutines -O2)
endif()

file(GLOB_RECURSE VORTEX_SRCS
        source/**.h
		source/**.cpp
		thirdParty/stb_image/**.h
		thirdParty/stb_image/**.cpp
		thirdParty/glm/glm/**.hpp
		thirdParty/glm/glm/**.inl
    )

include_directories(Vortex
		source
        thirdParty/SDL2/include
        thirdParty/assimp/include
	    thirdParty/glm
	    thirdParty/imgui
	    thirdParty/stb_image
        thirdParty/spdlog/include
	    thirdParty/Entt/include
    )

add_library(Vortex STATIC ${VORTEX_SRCS})
target_precompile_headers(Vortex PRIVATE source/vpch.h)
target_link_libraries(Vortex Vulkan::Vulkan SDL2::SDL2-static assimp imgui)
