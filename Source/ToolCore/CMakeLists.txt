add_definitions(-DCPLUSPLUS_WITHOUT_QT)

file (GLOB_RECURSE SOURCE_FILES *.cpp *.h)

add_library(ToolCore ${SOURCE_FILES})

target_link_libraries(ToolCore Assimp Poco Cross)

GroupSources("Assets")
GroupSources("Import")
GroupSources("Project")
GroupSources("Subprocess")
