#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#define GLEW_STATIC
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class TextureManager {
private:
    unsigned int textureID;
public:
    bool LoadTexture(const std::string &filePath = "content/defult.jpg");
    void BindTexture(unsigned int textureUnit = 0);
    void GetTextureID();
    void whiteTexture();
};

#endif
