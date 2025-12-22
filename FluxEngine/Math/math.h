#ifndef MATH_H
#define MATH_H

#include "../Vector/vec.h"
#include "../Matrix/matrix.h"
#include <cmath>

namespace fluxmath {
inline float radians(float degrees) {
    return degrees * 0.01745329252f;
}

inline mat4 translate(const mat4& m, const vec3& v) {
    mat4 result = m;
    result[3].x += v.x;
    result[3].y += v.y;
    result[3].z += v.z;
    return result;
}

inline mat4 rotate(const mat4& m, float angle, const vec3& axis) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    vec3 a = axis.normalized();

    mat4 rotation;
    rotation[0] = vec4(c + a.x*a.x*(1-c), a.y*a.x*(1-c) + a.z*s, a.z*a.x*(1-c) - a.y*s, 0);
    rotation[1] = vec4(a.x*a.y*(1-c) - a.z*s, c + a.y*a.y*(1-c), a.z*a.y*(1-c) + a.x*s, 0);
    rotation[2] = vec4(a.x*a.z*(1-c) + a.y*s, a.y*a.z*(1-c) - a.x*s, c + a.z*a.z*(1-c), 0);
    rotation[3] = vec4(0, 0, 0, 1);

    return rotation * m;
}

inline mat4 scale(const mat4& m, const vec3& v) {
    mat4 result = m;
    result[0] = result[0] * v.x;
    result[1] = result[1] * v.y;
    result[2] = result[2] * v.z;
    return result;
}

inline mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up) {
    vec3 f = (center - eye).normalized();
    vec3 r = vec3::cross(f, up).normalized();
    vec3 u = vec3::cross(r, f);

    mat4 result;
    result[0] = vec4(r.x, u.x, -f.x, 0);
    result[1] = vec4(r.y, u.y, -f.y, 0);
    result[2] = vec4(r.z, u.z, -f.z, 0);
    result[3] = vec4(-vec3::dot(r, eye), -vec3::dot(u, eye), vec3::dot(f, eye), 1);
    return result;
}
inline mat4 perspective(float fov, float aspect, float near, float far) {
    mat4 result;
    float tanHalfFov = std::tan(fov / 2.0f);
    float f = 1.0f / tanHalfFov;

    result[0] = vec4(f / aspect, 0, 0, 0);
    result[1] = vec4(0, f, 0, 0);
    result[2] = vec4(0, 0, -(far + near) / (far - near), -1.0f);
    result[3] = vec4(0, 0, -(2.0f * far * near) / (far - near), 0);
    return result;
}

inline vec3 normalize(const vec3& v) { return v.normalized(); }
inline vec3 cross(const vec3& a, const vec3& b) { return vec3::cross(a, b); }

inline const float* value_ptr(const mat4& m) {
    thread_local float data[16];
    for(int i = 0; i < 4; i++) {
        data[i*4 + 0] = m[i].x;
        data[i*4 + 1] = m[i].y;
        data[i*4 + 2] = m[i].z;
        data[i*4 + 3] = m[i].w;
    }
    return data;
}
}

#endif
