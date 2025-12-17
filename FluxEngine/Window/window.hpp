#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Shader/shaders.h"
#include "../Texture/texture.hpp"
#include "../Objects/object.hpp"
#include "../Map/map.hpp"

class Window {
private:
    GLFWwindow* window = nullptr;
    Shader* ourShader = nullptr;
    Map* currentMap = nullptr;
    Object object;

    unsigned int width, height, VBO, VAO, EBO;

    const char* title;

    Texture texture;

    glm::mat4 projection;
public:
    bool Create(const char* title = "FluxEngine", int width = 800, int height = 600);
    void SetMap(Map* map) { currentMap = map; }
    void Render();
    void Close();

};

#endif
