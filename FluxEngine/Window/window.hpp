#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Shader/shaders.h"
#include "../Texture/texture.hpp"

class Window {
private:
    GLFWwindow* window = nullptr;
    Shader* ourShader = nullptr;

    unsigned int width, height, VBO, VAO, EBO;

    const char* title;

    Texture texture;

    glm::mat4 projection;

    //void processInput(GLFWwindow* window)
    //void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    //float vertices;
public:
    bool Create(const char* title = "FluxEngine", int width = 800, int height = 600);
    void Render();
    void Close();
};

#endif
