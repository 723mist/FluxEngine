#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class EngineWindow{
    public:
        int width;
        int height;
        int Run(const char* title = "VE", int width = 500, int height = 500, bool resizeble = true);
};
