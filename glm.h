#ifndef GLM_H
#define GLM_H

#include <iostream>

class vec3 {
public:
    float a, b, c;
    vec3(float _a, float _b, float _c) : a(_a), b(_b), c(_c) {}
};

class mat4 {
public:
    float matrix[4][4];
    mat4() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                matrix[i][j] = 0.0f;
            }
        }
    }
};

#endif 
