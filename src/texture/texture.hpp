#ifndef WINDOW_HPP
#define WINDOW_HPP

#define GLEW_STATIC
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class TextureManager {
public:
    bool LoadTexture(const std::string &filePath = "content/defult.jpg");
    void BindTexture(unsigned int textureID = 1);
    void GetTextureID();
};

#endif
