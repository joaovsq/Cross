## This template is used to generate the CMakeFiles.txt for a Cpp Game Project
project(CppGame)

# Define source files
file (GLOB GAME_SOURCE_FILES Source/*.cpp Source/*.h)

if (WIN32)
    add_definitions(-DCROSS_WIN32_CONSOLE)
endif()
add_compile_definitions(CROSS_STATIC_DEFINE)

include_directories(C:/Projects/Engines/Cross/Source;C:/Projects/Engines/Cross/Source/ThirdParty)

add_library(GameLib )
target_link_libraries(GameLib PUBLIC C:/Projects/Engines/Cross/out/build/x64-Debug/Source/Cross/Cross.lib)

add_executable(CppGame Game.h Game.cpp)
target_link_libraries(CppGame GameLib)

if (MSVC)
    target_compile_options(CppGame PUBLIC $<$<CONFIG:Debug>:/MTd> $<$<NOT:$<CONFIG:Debug>>:/MT>)
endif ()

#[[
# Copy CrossTool to Artifacts
add_custom_command( TARGET FeatureExamples POST_BUILD
                    COMMAND "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe"
                    ARGS -E make_directory \"C:/Projects/Engines/Cross/Artifacts/Examples/CPlusPlus\"
                    COMMAND "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe"
                    ARGS -E copy_if_different \"$<TARGET_FILE:FeatureExamples>\" \"C:/Projects/Engines/Cross/Artifacts/Examples/CPlusPlus/\"
                    COMMENT "Copying FeatureExamples to Build Artifacts" )

if (WIN32)

  # pre-Windows 8 can't count on D3DCompiler_47.dll being on system
  add_custom_command (TARGET CppGame POST_BUILD
  COMMAND C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe
  ARGS -E copy_if_different \"C:/Projects/Engines/Cross/Build/Windows/Binaries/x64/D3DCompiler_47.dll\" \"$<TARGET_FILE_DIR:FeatureExamples>/D3DCompiler_47.dll\"
  COMMAND C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe
  ARGS -E copy_if_different \"C:/Projects/Engines/Cross/Build/Windows/Binaries/x64/D3DCompiler_47.dll\" \"C:/Projects/Engines/Cross/Artifacts/Examples/CPlusPlus/D3DCompiler_47.dll\" )

endif(WIN32)
]]
