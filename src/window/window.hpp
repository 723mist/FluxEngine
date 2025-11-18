#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
//#include <GLFW/glfw3.h> //

class Engine {
public:
    bool Init(const char* title = "VE", int width = 500, int height = 500);
    void Run();
    void Destroy();

    void BackgroundColor(double red = 0.0f, double green = 0.0f, double blue = 0.0f);
};

#endif
