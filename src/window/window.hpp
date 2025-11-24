#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Engine {
private:
    int width, height;
    GLFWwindow* window;
    unsigned int VBO, VAO, EBO, shaderProgram;

    bool FPS_Counter = false;
    unsigned frameCount = 0;
    double lastTime = 0;
    int frames = 0;
    const char* g_title;

    float color_r_f = 0.0f, color_g_f = 0.0f, color_b_f = 0.0f;

public:
    bool Init(const char* title = "VE", int width = 500, int height = 500);
    void Run();
    void Destroy();
    void BackgroundColor(double red = 0.0f, double green = 0.0f, double blue = 0.0f);
};

#endif
