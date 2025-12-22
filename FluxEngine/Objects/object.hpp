#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <string>
#include "../Texture/texture.hpp"

#include "Vector/vec.h"
#include "Matrix/matrix.h"
#include "Math/math.h"

class Object {
public:
    std::string name;
    vec3 position;
    vec3 rotation;
    vec3 scale;
    std::shared_ptr<Texture> texture;

    Object(const std::string& name = "Object") : name(name), position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}

    mat4 GetModelMatrix() const {
        mat4 model;
        model = fluxmath::translate(model, position);
        model = fluxmath::rotate(model, fluxmath::radians(rotation.x), vec3(1, 0, 0));
        model = fluxmath::rotate(model, fluxmath::radians(rotation.y), vec3(0, 1, 0));
        model = fluxmath::rotate(model, fluxmath::radians(rotation.z), vec3(0, 0, 1));
        model = fluxmath::scale(model, scale);
        return model;
    }

    void LoadTexture(const std::string& filePath) {
        texture = std::make_shared<Texture>();
        texture->LoadTexture(filePath);
    }

    void SetTexture(std::shared_ptr<Texture> tex) {
        texture = tex;
    }

    void BindTexture(unsigned int textureUnit = 0) {
        if (texture) {
            texture->BindTexture(textureUnit);
        }
    }
};
#endif
