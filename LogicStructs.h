#pragma once
#include <vector>

struct DoubleConstraint {
    double MaxValue, MinValue, Value;

    DoubleConstraint() : MaxValue(0), MinValue(0), Value(0) {}
    DoubleConstraint(double _Max, double _Min, double _Val) : MaxValue(_Max), MinValue(_Min), Value(_Val) {}
};

struct Vector3 {
    float x, y, z;
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    float Dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
};

struct Vector2 {
    float x, y;
    Vector2() : x(0), y(0) {}
    Vector2(float _x, float _y) : x(_x), y(_y) {}
};

struct Vector4 {
    float x, y, z, w;
};

struct Matrix4x4 {
    float m[4][4];
    float* operator[](int index) { return m[index]; }
    const float* operator[](int index) const { return m[index]; }
};