file (GLOB CONTAINER_SOURCE Container/*.cpp Container/*.h)
file (GLOB CORE_SOURCE Core/*.cpp Core/*.h)
file (GLOB MATH_SOURCE Math/*.cpp Math/*.h)
file (GLOB IO_SOURCE IO/*.cpp IO/*.h)
file (GLOB ENGINE_SOURCE Engine/*.cpp Engine/*.h)
file (GLOB INPUT_SOURCE Input/*.cpp Input/*.h)
file (GLOB RESOURCE_SOURCE Resource/*.cpp Resource/*.h)
file (GLOB AUDIO_SOURCE Audio/*.cpp Audio/*.h)
file (GLOB NETWORK_SOURCE Network/*.cpp Network/*.h)
file (GLOB WEB_SOURCE Web/*.cpp Web/*.h)
file (GLOB SCRIPT_SOURCE Script/*.cpp Script/*.h)
file (GLOB METRICS_SOURCE Metrics/*.cpp Metrics/*.h)
if (NOT ANDROID)
    file (GLOB IPC_SOURCE IPC/*.cpp IPC/*.h)
endif()
file (GLOB CROSS2D_SOURCE Cross2D/*.cpp Cross2D/*.h)
file (GLOB SCENE_SOURCE Scene/*.cpp Scene/*.h)
file (GLOB SYSTEM_UI_SOURCE UI/SystemUI/*.cpp UI/SystemUI/*.h)
file (GLOB PHYSICS_SOURCE Physics/*.cpp Physics/*.h)
file (GLOB NAVIGATION_SOURCE Navigation/*.cpp Navigation/*.h)
file (GLOB ENVIRONMENT_SOURCE Environment/*.cpp Environment/*.h)
file (GLOB GRAPHICS_SOURCE Graphics/*.cpp Graphics/*.h Graphics/Text3D/*.cpp Graphics/Text3D/*.h)
if (CROSS_IK)
    file (GLOB IK_SOURCE IK/*.cpp IK/*.h)
endif ()

if (CROSS_DATABASE_SQLITE)
    file (GLOB DATABASE_SOURCE Database/*.cpp Database/*.h Database/SQLite/*.cpp Database/SQLite/*.h)
elseif (CROSS_DATABASE_ODBC)
    file (GLOB DATABASE_SOURCE Database/*.cpp Database/*.h Database/ODBC/*.cpp Database/ODBC/*.h)
endif ()

if (WIN32)
    if (CROSS_D3D9) # DirectX 9
        file (GLOB GRAPHICS_IMPL_SOURCE Graphics/Direct3D9/*.cpp Graphics/Direct3D9/*.h)
    elseif (CROSS_OPENGL) # OpenGL
        file (GLOB GRAPHICS_IMPL_SOURCE Graphics/OpenGL/*.cpp Graphics/OpenGL/*.h)
    elseif(CROSS_D3D11) # DirectX 11
        file (GLOB GRAPHICS_IMPL_SOURCE Graphics/Direct3D11/*.cpp Graphics/Direct3D11/*.h)
    endif()
else()
    file (GLOB GRAPHICS_IMPL_SOURCE Graphics/OpenGL/*.cpp Graphics/OpenGL/*.h)
endif()

set (SOURCE_FILES ${CONTAINER_SOURCE} ${CORE_SOURCE} ${ENGINE_SOURCE} ${INPUT_SOURCE}
                  ${AUDIO_SOURCE} ${IO_SOURCE} ${MATH_SOURCE}
                  ${RESOURCE_SOURCE} ${PHYSICS_SOURCE} ${IPC_SOURCE}
                  ${GRAPHICS_SOURCE} ${GRAPHICS_IMPL_SOURCE}
                  ${CROSS3D_SOURCE}
                  ${CROSS2D_SOURCE} ${ENVIRONMENT_SOURCE}
                  ${SCENE_SOURCE} ${SYSTEM_UI_SOURCE}
                  ${WEB_SOURCE} ${SCRIPT_SOURCE} ${METRICS_SOURCE}
                  ${PLATFORM_SOURCE} ${DATABASE_SOURCE} ${IK_SOURCE} ${NAVIGATION_SOURCE})

set (SOURCE_FILES ${SOURCE_FILES} ${NETWORK_SOURCE})

GroupSources("Cross2D")
GroupSources("Cross3D")
GroupSources("Audio")
GroupSources("Container")
GroupSources("Core")
GroupSources("Engine")
GroupSources("Environment")
GroupSources("Graphics")
GroupSources("Input")
GroupSources("IO")
GroupSources("IPC")
GroupSources("Math")
GroupSources("Navigation")
GroupSources("Network")
GroupSources("Physics")
GroupSources("Resource")
GroupSources("Scene")
GroupSources("UI")
GroupSources("Web")
GroupSources("Script")
GroupSources("Metrics")
GroupSources("BuildInfo")
GroupSources("IK")

# Handle Git Revision
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/BuildInfo/CrossGitSHA.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/BuildInfo/CrossGitSHA.cpp" @ONLY)

set (SOURCE_FILES ${SOURCE_FILES} BuildInfo/CrossBuildInfo.cpp BuildInfo/CrossBuildInfo.h BuildInfo/CrossGitSHA.cpp BuildInfo/CrossGitSHA.h)

if (CROSS_DYNAMIC_RUNTIME)
    set(CROSS_LIBRARY_TYPE SHARED)
else ()
    set(CROSS_LIBRARY_TYPE STATIC)
endif ()
add_library(Cross ${CROSS_LIBRARY_TYPE} ${SOURCE_FILES})
if (NOT CROSS_DYNAMIC_RUNTIME)
    target_compile_definitions (Cross PUBLIC -DCROSS_STATIC_DEFINE=1 -DCROSS_API=)
else ()
    target_compile_definitions (Cross PRIVATE -DCROSS_EXPORTS=1)
endif ()

include_directories (${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Cross PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
target_link_libraries (Cross Box2D FreeType JO LZ4 PugiXml STB SDL ASIO rapidjson WebSocketPP imgui)
target_compile_definitions (Cross PUBLIC -DCROSS_CXX11=1)
if (CROSS_64BIT)
    target_compile_definitions (Cross PUBLIC -DCROSS_64BIT=1)
endif ()
if (ANDROID)
    target_link_libraries (Cross dl log android GLESv1_CM GLESv2)
    target_compile_definitions(Cross PUBLIC -DCROSS_PLATFORM_ANDROID=1 -DGLEW_NO_GLU=1)
elseif (LINUX)
    target_link_libraries (Cross pthread GLEW GL dl)
    target_compile_definitions(Cross PUBLIC -DCROSS_PLATFORM_LINUX=1)
elseif (WIN32)
    target_compile_definitions (Cross PUBLIC -DCROSS_PLATFORM_WINDOWS=1)
    target_link_libraries (Cross user32 gdi32 winmm imm32 ole32 oleaut32 version uuid Ws2_32)
    if (CROSS_D3D9) # DirectX 9
        target_link_libraries (Cross d3d9 d3dcompiler)
        target_compile_definitions (Cross PUBLIC -DCROSS_D3D9=1)
    elseif(CROSS_OPENGL) # OpenGL
        find_package(OpenGL REQUIRED)
        include_directories (${OpenGL_INCLUDE_DIRS})
        link_directories (${OpenGL_LIBRARY_DIRS})
        target_compile_definitions (Cross PRIVATE ${OpenGL_DEFINITIONS})
        target_link_libraries (Cross GLEW opengl32 glu32)
    elseif(CROSS_D3D11) # DirectX 11
        target_compile_definitions (Cross PUBLIC -DCROSS_D3D11=1)
        target_link_libraries (Cross d3d11 d3dcompiler dxguid)
    endif()
    target_link_libraries(Cross MojoShader user32 gdi32 winmm imm32 ole32 oleaut32 version uuid Ws2_32)

    # removes dependency on D3DCompiler dll for Cross Direct3D9 builds which don't require it
    # (binaries that never initialize the Direct3D9 graphics subsystem)
    option (CROSS_D3D9SHADERCOMPILER_DISABLE "Remove D3DCompiler.dll dependency. Use for binaries that never initialize the Direct3D9 graphics subsystem." OFF)
    if (CROSS_D3D9SHADERCOMPILER_DISABLE)
        target_compile_definitions (Cross PUBLIC -DCROSS_D3D9SHADERCOMPILER_DISABLE=1)
    endif()
elseif (WEB)
    target_compile_definitions(Cross PUBLIC -DCROSS_PLATFORM_WEB=1 -DNO_POPEN=1)
endif ()

if (CROSS_OPENGL)
    target_compile_definitions(Cross PUBLIC -DCROSS_OPENGL=1)
endif ()

if (CROSS_DESKTOP)
    target_compile_definitions (Cross PUBLIC -DCROSS_PLATFORM_DESKTOP=1)
    target_link_libraries (Cross libsquish)
    if (NOT LINUX)
        target_link_libraries (Cross LibCpuId)
    endif()
    option (CROSS_FILEWATCHER "Enable file watcher" ON)
    if (CROSS_FILEWATCHER)
        target_compile_definitions(Cross PUBLIC -DCROSS_FILEWATCHER=1)
    endif ()
endif ()

if (NOT WEB)
    target_compile_definitions (Cross PUBLIC -DCROSS_THREADING=1 -DCROSS_NETWORK=1 -DCROSS_WEB=1)
    target_link_libraries (Cross libcurl Civetweb kNet)
endif()

if (CROSS_PROFILING)
    target_compile_definitions (Cross PUBLIC -DCROSS_PROFILING=1)
    target_link_libraries (Cross easy_profiler)
endif ()

option (CROSS_LOGGING "Enable logging" ON)
if (CROSS_LOGGING)
    target_compile_definitions (Cross PUBLIC -DCROSS_LOGGING=1)
endif ()

option (CROSS_2D_ONLY "Build only with 2D support" OFF)
if (CROSS_2D_ONLY)
    target_compile_definitions (Cross PUBLIC -DCROSS_CROSS2D=1)
else ()
    target_compile_definitions (Cross PUBLIC -DCROSS_3D)

    option (CROSS_CROSS2D "Enable 2D subsystem" ON)
    if (CROSS_CROSS2D)
        target_compile_definitions (Cross PUBLIC -DCROSS_CROSS2D=1)
    endif ()

    option (CROSS_PHYSICS "Enable physics subsystem" ON)
    if (CROSS_PHYSICS)
        target_compile_definitions (Cross PUBLIC -DCROSS_PHYSICS=1)
        target_link_libraries (Cross Bullet StanHull)
    endif ()

    option (CROSS_NAVIGATION "Enable navigation subsystem" ON)
    if (CROSS_NAVIGATION)
        target_compile_definitions (Cross PUBLIC -DCROSS_NAVIGATION=1)
        target_link_libraries (Cross Recast Detour DetourCrowd DetourTileCache)
    endif ()
endif ()

target_compile_definitions (Cross PUBLIC -DCROSS_TBUI=1)

if (CROSS_DATABASE_SQLITE)
    target_link_libraries(Cross sqlite)
    target_compile_definitions(Cross PUBLIC -DCROSS_DATABASE=1 -DCROSS_DATABASE_SQLITE=1)
elseif (CROSS_DATABASE_ODBC)
    target_link_libraries(Cross nanodbc)
    target_compile_definitions(Cross PUBLIC -DCROSS_DATABASE=1 -DCROSS_DATABASE_ODBC=1)
endif ()

if (CROSS_IK)
    target_link_libraries(Cross ik)
    target_compile_definitions(Cross PUBLIC -DCROSS_IK=1)
endif ()

target_include_directories (Cross PUBLIC
    ${CROSS_SOURCE_DIR}/Source
    ${CROSS_SOURCE_DIR}/Source/ThirdParty
)

include(CrossDoc)

if ($ENV{CROSS_BUILD_DIST})
    target_compile_definitions(Cross PUBLIC -DCROSS_BUILD_DIST=1)
endif ()

if (MSVC)
    target_compile_options(Cross PUBLIC $<$<CONFIG:Debug>:${CROSS_MSVC_RUNTIME}d> $<$<NOT:$<CONFIG:Debug>>:${CROSS_MSVC_RUNTIME}>)
endif ()

if (UNIX OR MINGW)
    target_compile_options(Cross PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=gnu++11>)
endif ()
