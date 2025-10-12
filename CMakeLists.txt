cmake_minimum_required(VERSION 3.10)
project(VE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)

file(GLOB_RECURSE SOURCES
    src/*.*
    src/window/*.*
    src/objects/*.*
    src/filestructure/*.*
)

file(GLOB_RECURSE HEADERS
    src/*.*
    src/window/*.*
    src/objects/*.*
    src/filestructure/*.*
)

add_executable(VE
    src/main.cpp
    src/engine.h
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(VE PRIVATE
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(VE PRIVATE
    ${OPENGL_gl_LIBRARY}
    glfw
    GLEW::GLEW
)
