cmake_minimum_required(VERSION 3.5)
project(FluxEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SRC_DIR src)
set(LIBS_DIR libs)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
#find_package(Freetype REQUIRED)
find_package(glm REQUIRED)

add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${LIBS_DIR}/stb)

file(GLOB_RECURSE SOURCES
        ${SRC_DIR}/*.cpp
        ${SRC_DIR}/window/*.cpp
        ${SRC_DIR}/texture/*.cpp
        ${SRC_DIR}/renderer/*.cpp
)

file(GLOB_RECURSE HEADERS
        ${SRC_DIR}/*.hpp
        ${SRC_DIR}/*.h
        ${SRC_DIR}/window/*.hpp
        ${SRC_DIR}/texture/*.hpp
        ${SRC_DIR}/renderer/*.hpp
        ${SRC_DIR}/renderer/*.h
)

add_executable(FE
        src/main.cpp
        ${SOURCES}
        ${HEADERS}
)

target_include_directories(FE PRIVATE
        src
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(FE PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
        glm::glm
        stb_image
)
