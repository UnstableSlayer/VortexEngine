cmake_minimum_required(VERSION 3.7)
project(VortexEngine)

# Configuration types
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS  ${CMAKE_CONFIGURATION_TYPES})
endif()

set(${PROJ_NAME}_PATH_INSTALL     "/opt/project"                     CACHE PATH "This directory contains installation Path")
set(CMAKE_DEBUG_POSTFIX "d")

add_subdirectory(Vortex)
add_subdirectory(GameProject)
