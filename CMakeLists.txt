project(Cross)

cmake_minimum_required(VERSION 3.3)

#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_STANDARD_REQUIRED OFF)

set(CROSS_SOURCE_DIR ${Cross_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CROSS_SOURCE_DIR}/Build/CMake/Modules)
set(CROSS_DESKTOP TRUE)

include(CrossGit)
include(CrossUtils)
include(CrossCommon)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set (CROSS_RELEASE_OFF OFF)
    set (CROSS_RELEASE_ON ON)
else ()
    set (CROSS_RELEASE_OFF ON)
    set (CROSS_RELEASE_ON OFF)
endif ()

add_definitions(-DCROSS_ROOT_SOURCE_DIR="${CROSS_SOURCE_DIR}" -DCROSS_ROOT_BUILD_DIR="${CMAKE_BINARY_DIR}")

if (NOT DEFINED CROSS_DEV_BUILD)
    set(CROSS_DEV_BUILD 1)
ENDIF ()

if (CROSS_DEV_BUILD)
    add_definitions("-DCROSS_DEV_BUILD=1")
endif ()

include(CrossPlatform)

find_program(CLDOC cldoc)
if (CLDOC)
    add_custom_target(docs DEPENDS CrossEngineDocs)
endif ()

add_subdirectory(Source)

# This subdirectory is specific to the cpp games, using the engine as a library
add_subdirectory(Games)
