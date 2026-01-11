#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader/shaders.h"
#include "../Objects/object.hpp"
#include "../Map/map.hpp"
#include "../Vector/vec.h"
#include "../Matrix/matrix.h"
#include "../Math/math.h"
#include "../Camera/camera.h"
#include "../Sprite/sprite.h"

class Window {
private:
    GLFWwindow* window = nullptr;
    Shader* ourShader = nullptr;
    Shader* lightShader = nullptr;
    Shader* spriteShader = nullptr;
    Map* currentMap = nullptr;
    Object object;
    std::vector<Sprite> sprites;

    unsigned int width, height, VBO, VAO, EBO, lightVAO;

    const char* title;

    Texture texture;

    mat4 projection;
public:
    bool create(const char* title = "FluxEngine", int width = 800, int height = 600);
    void setMap(Map* map) { currentMap = map; }
    void addSprite(const Sprite& sprite);
    void drawSpriteList();
    void render();
    void close();
};

#endif
