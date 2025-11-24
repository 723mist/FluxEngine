#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <GL/glew.h>

class Engine {
private:
    int width, height;
public:
    bool Init(const char* title = "VE", int width = 500, int height = 500);
    void Run();
    void Destroy();

    void BackgroundColor(double red = 0.0f, double green = 0.0f, double blue = 0.0f);
};

class Debug {
public:
    void FPSCounter(double updateTime = 0.3);
};

#endif
