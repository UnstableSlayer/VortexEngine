set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE GAMEPROJECT_SRCS source/*.h source/*.cpp)

add_executable(GameProject ${GAMEPROJECT_SRCS})
include_directories(GameProject
		../Vortex/source
		../Vortex/thirdParty/glm
        ../Vortex/thirdParty/spdlog/include
		../Vortex/thirdParty/Entt/include
    )

target_link_libraries(GameProject Vortex)
