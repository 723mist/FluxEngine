#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Shader/shaders.h"

class Window {
private:
    GLFWwindow* window = nullptr;
    Shader* ourShader = nullptr;

    unsigned int width, height, VBO, VAO, EBO;

    const char* title;

    //float vertices;
public:
    bool create(const char* title = "FluxEngine", int width = 500, int height = 500);
    void stop();
    void renderLoop();
};

#endif
