project(Editor)

# Define source files
include(Sources.cmake)

if (WIN32)
    add_definitions(-DCROSS_WIN32_CONSOLE)
endif()

add_executable(Editor ${EDITOR_SOURCE_FILES})
target_link_libraries(Editor Cross ToolCore)

