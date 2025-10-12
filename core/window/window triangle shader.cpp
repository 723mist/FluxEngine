/*#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.hpp"
#include <iostream>
#include "../graphics/triangle.hpp"
//#include <vector>

int EngineWindow::Run(const char* title, int width, int height, bool resizeble){

    const char *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    //Fragment shader
    const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"

        "void main()\n"
        "{\n"
        "    FragColor = vec4(0.9f, 0.5f, 0.1f, 1.0f);\n"
        "}\0" ;

    if (!glfwInit()){ std::cout << "Error init GLFW" << std::endl; }

    if (resizeble == true) {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    }
    else {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }

    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!window) {
        std::cerr << "Error create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "Error init GLEW: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
        return -1;
    }

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glOrtho(-width/2, width/2, -height/2, height/2, -1, 1);
    //glMatrixMode(GL_MODELVIEW);
    //glViewport(0, 0, width, height);
    glEnable(GL_VERTEX_ARRAY);

    //TEST
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f
    };

    // Setting the buffer, array and shader variables :
    unsigned int VBO;
    unsigned int VAO;

    unsigned int v_shader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int f_shader = glCreateShader(GL_FRAGMENT_SHADER);

    // Setting up the buffer :

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices, GL_STATIC_DRAW);

    unsigned int shaderProgram = glCreateProgram();

    glShaderSource(v_shader,1,&vertexShaderSource,NULL);
    glCompileShader(v_shader);

    int success;
    char infoLog[512];
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(v_shader, 512, NULL, infoLog);
        std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
    }

    glShaderSource(f_shader,1,&fragmentShaderSource,NULL);
    glCompileShader(f_shader);

    glAttachShader(shaderProgram,v_shader);
    glAttachShader(shaderProgram,f_shader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
    }

    glDeleteShader(v_shader);
    glDeleteShader(f_shader);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3* sizeof(float), (void*)0);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES,0,3);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
*/
