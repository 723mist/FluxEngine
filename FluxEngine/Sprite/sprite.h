#ifndef SPRITE_H
#define SPRITE_H

#include "Vector/vec.h"
#include "Texture/texture.hpp"
#include <string>

class Sprite {
public:
    vec2 position;
    vec1 rotation;
    vec2 size;
    Texture texture;

    Sprite() : position(0, 0), rotation(0), size(1, 1) {}
    Sprite(const std::string& texPath) : position(0, 0), rotation(0), size(1, 1) {
        texture.setTexture(texPath);
    }

    void setTexture(const std::string& filePath) {
        texture.setTexture(filePath);
    }

    void Draw() {}
};

#endif
