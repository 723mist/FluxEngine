#ifndef MATRIX_H
#define MATRIX_H

#include "../Vector/vec.h"

struct mat4 {
    vec4 data[4];

    mat4() { identity(); }

    void identity() {
        data[0] = vec4(1,0,0,0);
        data[1] = vec4(0,1,0,0);
        data[2] = vec4(0,0,1,0);
        data[3] = vec4(0,0,0,1);
    }

    vec4& operator[](int i) { return data[i]; }
    const vec4& operator[](int i) const { return data[i]; }

    mat4 operator*(const mat4& other) const {
        mat4 result;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                float sum = 0.0f;
                for(int k = 0; k < 4; k++) {
                    sum += data[k][j] * other[i][k];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }
};

#endif
