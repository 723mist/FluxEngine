#include "window.hpp"
#include "iostream"
#include "GLES2/gl2.h"

void Engine::FPS(bool FPS_in_title, bool FPS_in_console){
    tFPS = FPS_in_title;
    cFPS = FPS_in_console;
}

void Engine::UpdateFPS(double time_for_update_FPS) {
    uFPS = time_for_update_FPS;
}

void Engine::VSync(bool VSync){
    if (VSync == true) {
        VSYNC = 0;
    }
    else {
        VSYNC = 1;
    }
}

int Engine::Window(const char* title, int width, int height, bool resize){

    //GLFW Init
    if (!glfwInit()){
        std::cout << "Error: glfwInit" << std::endl;
        return -1;
    }

    //Resize
    if (resize == true) { glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); }
    else { glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); }

    //Create window
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    //Debug window
    if (!window) {
        std::cout << "Error: window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Set render opengl
    glfwMakeContextCurrent(window);

    //VSync
    glfwSwapInterval(VSYNC);

    //Window size "width x height"
    std::cout << width << "x" << height << std::endl;

    //All for FPS counter
    static unsigned frameCount = 0;
    double lastTime = glfwGetTime();
    int frames = 0;

    //All in window
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        frames++;
        double currentTime = glfwGetTime();
        if (tFPS == true) {
            if (currentTime - lastTime >= uFPS) {
                double fps = frames / (currentTime - lastTime);
                std::string titleWithFPS = std::string(title) + " FPS: " + std::to_string((int)fps); // 60 fps != 60.000 std::to_string((int)fps)
                glfwSetWindowTitle(window, titleWithFPS.c_str());
                frames = 0;
                lastTime = currentTime;
            }
        }
        if (cFPS == true) {
            if (currentTime - lastTime >= uFPS) {
                double fps = frames / (currentTime - lastTime);
                if (fps >= 30){
                    std::cout << "FPS: " << (int)fps << std::endl; // 60 fps != 60.000 (int)fps
                }
                else {
                    std::cout << "FPS: " << (int)fps << " Perhaps fps is unstable!" << std::endl;
                }
                frames = 0;
                lastTime = currentTime;
            }
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    //Window close
    std::cout << "Window close" << std::endl;

    //Close ALL window
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
