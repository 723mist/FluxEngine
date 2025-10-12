#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.hpp"
#include <iostream>

int EngineWindow::Run(const char* title, int width, int height, bool resizeble){

    if (!glfwInit()){ std::cout << "Error init GLFW" << std::endl; }

    if (resizeble == true) { glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); }
    else { glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); }

    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!window) {
        std::cerr << "Error create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
