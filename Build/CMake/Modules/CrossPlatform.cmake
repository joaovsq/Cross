
set(CROSS_DYNAMIC_RUNTIME OFF CACHE BOOL "Build engine as shared library and link dynamically to system runtime.")

if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Darwin")
    set(CROSS_NODE_JAKE Build/Mac/node/node Build/node_modules/jake/bin/cli.js -f Build/Scripts/Bootstrap.js)
endif()
if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Linux")
    set(CROSS_NODE_JAKE Build/Linux/node/node Build/node_modules/jake/bin/cli.js -f Build/Scripts/Bootstrap.js)
endif()
if("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Windows")
    set(CROSS_NODE_JAKE Build/Windows/node/node.exe Build/node_modules/jake/bin/cli.js -f Build\\Scripts\\Bootstrap.js)
endif()


if (WIN32)
    include(CrossWindows)
elseif (APPLE)
    if (IOS)
        include(CrossIOS)
    else ()
        include(CrossMac)
    endif ()
elseif (LINUX)
    include(CrossLinux)
elseif (ANDROID)
    include(CrossAndroid)
elseif (WEB)
    include(CrossWeb)
endif ()

if (NOT WIN32)
    set(CROSS_OPENGL 1)
endif ()

message(STATUS "Cross platform: ${JAVASCRIPT_BINDINGS_PLATFORM}")

set(JAVASCRIPT_BINDINGS_PLATFORM_ROOT "${CROSS_SOURCE_DIR}/Artifacts/Build/Source/Generated")

if (NOT EXISTS "${JAVASCRIPT_BINDINGS_PLATFORM_ROOT}/Javascript")
    execute_process(COMMAND ${CROSS_NODE_JAKE};build:precreateScriptBindings[${JAVASCRIPT_BINDINGS_PLATFORM}]
        WORKING_DIRECTORY "${CROSS_SOURCE_DIR}")
endif ()

file(GLOB_RECURSE JAVASCRIPT_BINDINGS_NATIVE_FILENAMES ${JAVASCRIPT_BINDINGS_PLATFORM_ROOT}/*.cpp ${JAVASCRIPT_BINDINGS_PLATFORM_ROOT}/*.h)
