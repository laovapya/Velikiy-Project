#ifndef GLM_H
#define GLM_H
#include <iostream>
#include <cmath>
#include <stdexcept>

class vec3 {
public:
    float a, b, c;
    vec3(float _a, float _b, float _c) : a(_a), b(_b), c(_c) {}

    float& operator[](int i) {
        if (i == 0) return a;
        else if (i == 1) return b;
        else if (i == 2) return c;
        throw std::out_of_range("Index out of range");
    }

    const float& operator[](int j) const {
        if (j == 0) return a;
        else if (j == 1) return b;
        else if (j == 2) return c;
        throw std::out_of_range("Index out of range");
    }

    vec3 operator-(const vec3& v) const {
        return vec3(a - v.a, b - v.b, c - v.c);
    }
};

inline float length(const vec3& v) {
    return std::sqrt(v.a * v.a + v.b * v.b + v.c * v.c);
}

inline vec3 normalize(const vec3& v) {
    float len = length(v);
    if (len != 0.0f) {
        return vec3(v.a / len, v.b / len, v.c / len);
    } else {
        return v;
    }
}

inline float dot(const vec3& v1, const vec3& v2) {
    return v1.a * v2.a + v1.b * v2.b + v1.c * v2.c;
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3(
        v1.b * v2.c - v1.c * v2.b,
        v1.c * v2.a - v1.a * v2.c,
        v1.a * v2.b - v1.b * v2.a
    );
}

class mat4 {
public:
    float matrix[4][4];

    mat4() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                matrix[i][j] = 0.0f;
            }
        }
    }

    float* operator[](int i) {
        return matrix[i];
    }

    const float* operator[](int j) const {
        return matrix[j];
    }

    static mat4 perspective(float field, float aspect, float near, float far) {
        mat4 res;
        float tan_half_f = tan(field / 2.0f);
        res[0][0] = 1.0f / (aspect * tan_half_f);
        res[1][1] = 1.0f / tan_half_f;
        res[2][2] = (far + near) / (near - far);
        res[2][3] = -1.0f;
        res[3][2] = (2.0f * far * near) / (near - far);
        return res;
    }

    static mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up) {
        vec3 f = normalize(center - eye);
        vec3 s = normalize(cross(up, f));
        vec3 u = cross(f, s);
        mat4 res;
        res[0][0] = s[0];
        res[1][0] = s[1];
        res[2][0] = s[2];
        res[0][1] = u[0];
        res[1][1] = u[1];
        res[2][1] = u[2];
        res[0][2] = -f[0];
        res[1][2] = -f[1];
        res[2][2] = -f[2];
        res[3][0] = -dot(s, eye);
        res[3][1] = -dot(u, eye);
        res[3][2] = dot(f, eye);
        res[3][3] = 1.0f;
        return res;
    }
            
    static mat4 multiply(const mat4& m1, const mat4& m2) {
        mat4 res;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                res[i][j] = 0.0f;
                for (int k = 0; k < 4; ++k) {
                    res[i][j] += m1[i][k] * m2[k][j];
                }
            }
        }
        return res;
    }
};

inline float radians(float deg) {
    return deg * static_cast<float>(M_PI) / 180.0f;
}

#endif 
