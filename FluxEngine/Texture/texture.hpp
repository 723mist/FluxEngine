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
    unsigned int setTexture(const std::string &filePath = "Content/placeholder.jpg");
    void bindTexture(unsigned int textureUnit = 0);
    unsigned int getTextureID() { return textureID; }
    void whiteTexture();
};

#endif
