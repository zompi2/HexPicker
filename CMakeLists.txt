#######################################
# Simple Hex Picker CMakeLists file 
# for generating project solutions.
#
# (c) 2020 Damian Nowakowski
#######################################

cmake_minimum_required(VERSION 3.0.0)
project(HexPicker VERSION 1.0.0)

# It requires OpenGL
find_package(OpenGL REQUIRED)

# Search for GLFW includes and lib
set (SFML_INCLUDE_DIR "" CACHE PATH "Libs")

set (SFML_MAIN_LIB "" CACHE FILEPATH "Libs")
set (SFML_GRAPHICS_LIB "" CACHE FILEPATH "Libs")
set (SFML_SYSTEM_LIB "" CACHE FILEPATH "Libs")
set (SFML_WINDOW_LIB "" CACHE FILEPATH "Libs")

set (JPEG_LIB "" CACHE FILEPATH "Libs")

# Search for all sources
set (SRC_FILES Src/Main.cpp)
set (SRC_FILES ${SRC_FILES} 
    Src/Board.cpp
    Src/BoardFlat.cpp 
    Src/BoardPointy.cpp
    Src/Engine.cpp
    Src/Scene.cpp
    Src/Tile.cpp)
set (SRC_FILES ${SRC_FILES} 
    ExternalSrc/inih/ini.c 
    ExternalSrc/inih/cpp/INIReader.cpp)

# Search and setup all includes
set (INCLUDE_DIRS ExternalSrc ${SFML_INCLUDE_DIR})
include_directories (${INCLUDE_DIRS})

# Setup output path
set (EXECUTABLE_OUTPUT_PATH ../Output)

# Setup executable and link with libraries
add_executable (HexPicker ${SRC_FILES})
target_compile_definitions (HexPicker PUBLIC SFML_STATIC)
target_link_libraries (HexPicker 
    ${OPENGL_LIBRARIES} 
    ${SFML_MAIN_LIB} 
    ${SFML_GRAPHICS_LIB}
    ${SFML_SYSTEM_LIB} 
    ${SFML_WINDOW_LIB} 
    ${JPEG_LIB} 
    winmm.lib)