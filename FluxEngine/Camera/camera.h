#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "Vector/vec.h"

static float FOV_3D = 45;
static float FOV_2D = 45;

class Camera3D {
private:
    float customCameraFOV;
    std::string name;
    vec3 position;
    vec3 rotation;
    float CFOV_3D = FOV_3D;

public:
    Camera3D(const std::string name = "Camera") : name(name), position(0, 0, 0), rotation(0, 0, 0) {}

    float GetCameraFOV() { return FOV_3D; }
    void SetCameraFOV() { CFOV_3D = FOV_3D; }
};

class Camera2D {
private:
    float customCameraFOV;
    std::string name;
    vec2 position;
    vec1 rotation;
    float CFOV_2D = FOV_2D;

public:
    Camera2D(const std::string name = "Camera") : name(name), position(0, 0), rotation(0) {}

    float GetCameraFOV() { return FOV_2D; }
    void SetCameraFOV() { CFOV_2D = FOV_2D; }
};

#endif
