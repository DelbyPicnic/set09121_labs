cmake_minimum_required(VERSION 3.9)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -stdlib=libc++")

project(Games_Engineering)

### Setup Directories ###
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Output all DLLs from all libs into main build folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

### Add External Deps ###
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

### Practical 1 ###
file(GLOB_RECURSE SOURCES practical_1/*.cpp prctical_1/*.h)
add_executable(PRACTICAL_1 ${SOURCES})
target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})
target_link_libraries(PRACTICAL_1 sfml-graphics)

### PONG ###
file(GLOB_RECURSE SOURCES pong/*.cpp pong/*.h)
add_executable(PONG ${SOURCES})
target_include_directories(PONG PRIVATE ${SFML_INCS})
target_link_libraries(PONG sfml-graphics)

### SPACE INVADERS ###
file(GLOB_RECURSE SOURCES space_invaders/*.cpp space_invaders/*.h)
add_executable(SPACE_INVADERS ${SOURCES})
target_include_directories(SPACE_INVADERS PRIVATE ${SFML_INCS})
target_link_libraries(SPACE_INVADERS sfml-graphics)
set_target_properties(SPACE_INVADERS PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)
add_dependencies(SPACE_INVADERS copy_resources)

### TILE-BASED GAME ENGINE ###

### MATHS LIBRARY ###
add_library(maths_lib INTERFACE)
target_sources(maths_lib INTERFACE "${CMAKE_SOURCE_DIR}/engine/maths_lib/maths.h")
target_include_directories(maths_lib INTERFACE "${CMAKE_SOURCE_DIR}/engine/maths_lib" SYSTEM INTERFACE ${SFML_INCS})

### TILE ENGINE LIBRARY ###
file(GLOB_RECURSE SOURCE_FILES engine/tile_engine_lib/*.cpp engine/tile_engine_lib/*.h)
add_library(tile_engine_lib STATIC ${SOURCE_FILES})
target_include_directories(tile_engine_lib PRIVATE ${SFML_INCS} INTERFACE "${CMAKE_SOURCE_DIR}/engine/tile_engine_lib/")
target_link_libraries(tile_engine_lib maths_lib sfml-graphics)

### TILE ENGINE ###
file(GLOB_RECURSE SOURCES tile_engine/*.cpp tile_engine/*.h)
add_executable(TILES ${SOURCES})
target_include_directories(TILES PRIVATE ${SFML_INCS})
target_link_libraries(TILES tile_engine_lib maths_lib sfml-graphics)

### PACMAN ###
file(GLOB_RECURSE SOURCES pacman/*.cpp pacman/*.h)
add_executable(PACMAN ${SOURCES})
target_include_directories(PACMAN PRIVATE ${SFML_INCS})
target_link_libraries(PACMAN sfml-graphics)


