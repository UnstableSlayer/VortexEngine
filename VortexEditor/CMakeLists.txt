set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE VORTEXEDITOR_SRCS source/*.h source/*.cpp)

add_executable(VortexEditor ${VORTEXEDITOR_SRCS})
include_directories(VortexEditor
		../Vortex/source
		../Vortex/thirdParty/glm
        	../Vortex/thirdParty/spdlog/include
		../Vortex/thirdParty/Entt/include
    )

target_link_libraries(VortexEditor Vortex)
