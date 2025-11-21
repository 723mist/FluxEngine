cmake_minimum_required(VERSION 3.5)
project(VE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)
find_package(glm REQUIRED)

file(GLOB_RECURSE SOURCES
        src/*.cpp
        src/window/*.cpp
        src/texture/*.cpp
)

file(GLOB_RECURSE HEADERS
        src/*.hpp
        src/*.h
        src/window/*.hpp
        src/texture/*.hpp
)

add_executable(VE
        src/main.cpp
        ${SOURCES}
        ${HEADERS}
)

target_include_directories(VE PRIVATE
        src
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(VE PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
        glm::glm
)
