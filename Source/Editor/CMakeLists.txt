project(CrossEditor)

# Define source files
include(Sources.cmake)

if (WIN32)
    add_definitions(-DCROSS_WIN32_CONSOLE)
endif()

add_executable(CrossEditor ${EDITOR_SOURCE_FILES})
target_link_libraries(CrossEditor Cross ToolCore)

