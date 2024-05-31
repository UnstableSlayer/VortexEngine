set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE TESTGAME_SRCS source/*.h source/*.cpp)

add_executable(TestGame ${TESTGAME_SRCS})
include_directories(TestGame
		../Vortex/source
		../Vortex/thirdParty/glm
        ../Vortex/thirdParty/spdlog/include
		../Vortex/thirdParty/Entt/include
    )

target_link_libraries(TestGame Vortex)
