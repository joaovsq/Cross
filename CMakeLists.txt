project(Cross)

cmake_minimum_required(VERSION 3.3)

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

if (CROSS_DESKTOP AND CROSS_DEV_BUILD)
	
	# This subdirectory is specific to the cpp games, using the engine as a library
	# add_subdirectory(Submodules/CppGames)

	#[[    if (NOT DEFINED CROSS_CPLUSPLUS_EXAMPLES)
        set(CROSS_CPLUSPLUS_EXAMPLES 1)
    endif ()
    if (CROSS_CPLUSPLUS_EXAMPLES)
        initialize_submodule(${CROSS_SOURCE_DIR}/Submodules/CrossExamples CROSS_CPLUSPLUS_EXAMPLES)
        if (CROSS_CPLUSPLUS_EXAMPLES)
            add_subdirectory(Submodules/CrossExamples/FeatureExamples/CPlusPlus)
        endif ()
    endif ()
	]]
endif ()