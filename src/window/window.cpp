#define STB_IMAGE_IMPLEMENTATION
#include "../texture/texture.hpp"
#include "window.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* VERTEX_SHADER_SOURCE = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;
    layout (location = 2) in vec2 aTexCoord;

    out vec3 ourColor;
    out vec2 TexCoord;

    uniform mat4 transform;

    void main()
    {
        gl_Position = transform * vec4(aPos, 1.0);
        ourColor = aColor;
        TexCoord = aTexCoord;
    }
)";

const char* FRAGMENT_SHADER_SOURCE = R"(
    #version 330 core
    in vec3 ourColor;
    in vec2 TexCoord;

    out vec4 FragColor;

    uniform sampler2D ourTexture;

    void main()
    {
        FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    }
)";

float color_r_f, color_g_f, color_b_f = 0.0;

GLFWwindow* window;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

unsigned int VBO, VAO, EBO, shaderProgram, g_width, g_height;
double g_updateTime;

const char* g_title;

//FPS
bool FPS_Counter = false;
static unsigned frameCount = 0;
double lastTime = glfwGetTime();
int frames = 0;

bool Engine::Init(const char* title, int width, int height) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwShowWindow(window);

    glfwSwapInterval(1); //VSync

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    //Vertices
    float vertices[] = {
    //       Position     |      Color
    //    X     Y     Z   |  R     G     B  | Textur_Pos
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Right, up
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Right, down
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Left, down
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Left, Up
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glViewport(0, 0, width, height);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VERTEX_SHADER_SOURCE, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FRAGMENT_SHADER_SOURCE, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //VBO VAO EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    TextureManager tm;
    tm.whiteTexture();

    g_width = width;
    g_height = height;
    g_title = title;

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    return true;
}

void Engine::BackgroundColor(double red, double green, double blue) {
    if (!(red > 1.0 || red < 0.0)) { color_r_f = red; } else { std::cout << "The color is specified incorrectly" << std::endl; }
    if (!(green > 1.0 || green < 0.0)) { color_g_f = green; } else { std::cout << "The color is specified incorrectly" << std::endl; }
    if (!(blue > 1.0 || blue < 0.0)) { color_b_f = blue; } else { std::cout << "The color is specified incorrectly" << std::endl; }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Debug::FPSCounter(double updateTime) {
    FPS_Counter = true;
    g_updateTime = updateTime;
}

void Engine::Run() {
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(color_r_f, color_g_f, color_b_f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        frames++;
        double currentTime = glfwGetTime();
        if (FPS_Counter) {
            if (currentTime - lastTime >= g_updateTime) {
                double fps = frames / (currentTime - lastTime);
                std::string titleWithFPS = std::string(g_title) + " FPS: " + std::to_string((int)fps); // 60 fps != 60.000 std::to_string((int)fps)
                glfwSetWindowTitle(window, titleWithFPS.c_str());
                std::cout << "FPS: " << (int)fps << std::endl; // 60 fps != 60.000 (int)fps
                frames = 0;
                lastTime = currentTime;
            }
        }

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        float aspect = (float)width / (float)height;

        float orthoLeft = -1.0f, orthoRight = 1.0f;
        float orthoBottom = -1.0f, orthoTop = 1.0f;

        if (aspect > 1.0f) {
            orthoLeft *= aspect;
            orthoRight *= aspect;
        } else {
            orthoBottom /= aspect;
            orthoTop /= aspect;
        }

        glm::mat4 projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, -1.0f, 1.0f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

        glm::mat4 transform = projection * model;

        glUseProgram(shaderProgram);
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        //glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }
}

void Engine::Destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
}

