#ifndef VEC_H
#define VEC_H

#include <cmath>

struct  vec1 {
    float x;

    vec1() : x(0) {}
    vec1(float x_init) : x(x_init) {}

    //Operators
    vec1 operator+(const vec1& v) const { return vec1(x + v.x); } //Operator +
    vec1 operator-(const vec1& v) const { return vec1(x - v.x); } //Operator -
    vec1 operator*(float s) const { return vec1(x * s); } //Operator *
    vec1 operator/(float s) const { return vec1(x / s); } //Operator /
    vec1& operator+=(const vec1& v) { x += v.x; return *this; } //Operator +=
    vec1& operator-=(const vec1& v) { x -= v.x; return *this; } //Operator -=

    vec1& operator*=(float s) { x *= s; return *this; }

    //Arithmetic operators
    float length() const { return std::abs(x); }
    vec1 normalized() const { float len = length(); return len > 0 ? *this / len : *this; }

    static float dot(const vec1& a, const vec1& b) { return a.x * b.x; }

};

struct vec2 {
    float x, y;

    vec2() : x(0), y(0) {}
    vec2(float x, float y) : x(x), y(y) {}

    //Operators
    vec2 operator+(const vec2& v) const { return vec2(x + v.x, y + v.y); } //Operator +
    vec2 operator-(const vec2& v) const { return vec2(x - v.x, y - v.y); } //Operator -
    vec2 operator*(float s) const { return vec2(x * s, y * s); } //Operator *
    vec2 operator/(float s) const { return vec2(x / s, y / s); } //Operator /
    vec2& operator+=(const vec2& v) { x += v.x; y += v.y; return *this; } //Operator +-=
    vec2& operator-=(const vec2& v) { x -= v.x; y -= v.y; return *this; } //Operator -=
    vec2& operator*=(float s) { x *= s; y *= s; return *this; } //Operator *=

    //Arithmetic operators
    float length() const { return std::sqrt(x*x + y*y); }
    vec2 normalized() const { float len = length(); return len > 0 ? *this / len : *this; }

    static float dot(const vec2& a, const vec2& b) { return a.x*b.x + a.y*b.y; }
    static vec2 cross(const vec2& a, const vec2& b) { return vec2(0, 0); }
};

struct vec3 {
    float x, y, z;

    vec3() : x(0), y(0), z(0) {}
    vec3(float x_init, float y_init, float z_init) : x(x_init), y(y_init), z(z_init) {}

    //Operators
    vec3 operator+(const vec3& v) const { return vec3(x + v.x, y + v.y, z + v.z); } //Operator +
    vec3 operator-(const vec3& v) const { return vec3(x - v.x, y - v.y, z - v.z); } //Operator -

    vec3 operator*(float s) const { return vec3(x * s, y * s, z * s); } //Operator *
    vec3 operator*(const vec3& v) const { return vec3(x * v.x, y * v.y, z * v.z); } //Operator * vector
    vec3 operator/(float s) const { return vec3(x / s, y / s, z / s); } //Operator /

    vec3& operator+=(const vec3& v) { x += v.x; y += v.y; z += v.z; return *this; } //Operator +=
    vec3& operator-=(const vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; } //Operator -=
    vec3& operator*=(float s) { x *= s; y *= s; z *= s; return *this; } //Operator *=

    //Arithmetic operators
    float length() const { return std::sqrt(x*x + y*y + z*z); }
    vec3 normalized() const { float len = length(); return len > 0 ? *this / len : *this;}

    static float dot(const vec3& a, const vec3& b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
    static vec3 cross(const vec3& a, const vec3& b) { return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x); }
};

struct vec4 {
    union {
        struct { float x, y, z, w; };
        float data[4];
    };

    //Operators
    vec4() : x(0), y(0), z(0), w(0) {}
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    vec4(float xx) : x(xx), y(0), z(0), w(0) {}
    vec4(float xx, float yy) : x(xx), y(yy), z(0), w(0) {}

    vec4 operator+(const vec4& v) const { return vec4(x + v.x, y + v.y, z + v.z, w + v.w); } //Operator +
    vec4 operator-(const vec4& v) const { return vec4(x - v.x, y - v.y, z - v.z, w - v.w); } //Operator +
    vec4 operator*(float s) const { return vec4(x * s, y * s, z * s, w * s); } //Operator *
    vec4 operator/(float s) const { return vec4(x / s, y / s, z / s, w / s); } //Operator /

    //Arithmetic operators
    float& operator[](int i) { return data[i]; }
    const float& operator[](int i) const { return data[i]; }
};



#endif

