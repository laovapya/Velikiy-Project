#pragma once
#include <iostream>
#include <cmath>

class vec3 {
private:
    const float pi = 3.14159265358979323846;



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
    }
    else {
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

//inline float radians(float deg) {
//    return deg * static_cast<float>(pi) / 180.0f;
//}

