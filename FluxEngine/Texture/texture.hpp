#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#define GLEW_STATIC
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Texture {
private:
    unsigned int textureID = 0;
public:
    unsigned int LoadTexture(const std::string &filePath = "Content/placeholder.jpg");
    void BindTexture(unsigned int textureUnit = 0);
    unsigned int GetTextureID() { return textureID; }
    void whiteTexture();
};

#endif
