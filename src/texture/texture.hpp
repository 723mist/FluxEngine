#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <GL/glew.h>

class TextureManager {
public:
    static unsigned int LoadTexture(const std::string& filePath);
    static void BindTexture(unsigned int textureID);
    static void DeleteTexture(unsigned int textureID);
};

#endif
