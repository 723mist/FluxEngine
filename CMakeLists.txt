cmake_minimum_required(VERSION 3.5)
project(FluxEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

file(GLOB_RECURSE SOURCES
        FluxEngine/*.cpp
        FluxEngine/Render/*.cpp
        FluxEngine/Texture/.cpp
        FluxEngine/Window/*.cpp
        FluxEngine/Loader/*.cpp
)

file(GLOB_RECURSE HEADERS
        FluxEngine/*.h
        FluxEngine/Render/*.h
        FluxEngine/Objects/*.h
        FluxEngine/Vector/*.h
        FluxEngine/Matrix/*.h

        FluxEngine/*.hpp
        FluxEngine/Window/*.hpp
        FluxEngine/Texture/*.hpp
        FluxEngine/Objects/*.hpp
        FluxEngine/Loader/*.hpp
        FluxEngine/Map/*.hpp
)

add_executable(FE
        FluxEngine/main.cpp
        ${SOURCES}
        ${HEADERS}
)

target_include_directories(FE PRIVATE
        FluxEngine
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(FE PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
        glm::glm
)
