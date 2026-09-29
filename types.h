#pragma once
#include <cstdint>
#include <cmath>
namespace types
{
    struct vector2_t
    {
        float x{}, y{};
        vector2_t() = default;
        vector2_t(float x, float y) : x(x), y(y) {}
        vector2_t operator+(const vector2_t& other) const { return { x + other.x, y + other.y }; }
        vector2_t operator-(const vector2_t& other) const { return { x - other.x, y - other.y }; }
        vector2_t operator*(float scalar) const { return { x * scalar, y * scalar }; }
        float length() const { return std::sqrtf(x * x + y * y); }
        float distance(const vector2_t& other) const { return (*this - other).length(); }
    };
    struct vector3_t
    {
        float x{}, y{}, z{};
        vector3_t() = default;
        vector3_t(float x, float y, float z) : x(x), y(y), z(z) {}
        vector3_t operator+(const vector3_t& other) const { return { x + other.x, y + other.y, z + other.z }; }
        vector3_t operator-(const vector3_t& other) const { return { x - other.x, y - other.y, z - other.z }; }
        vector3_t operator*(float scalar) const { return { x * scalar, y * scalar, z * scalar }; }
        float length() const { return std::sqrtf(x * x + y * y + z * z); }
        float distance(const vector3_t& other) const { return (*this - other).length(); }
        float dot(const vector3_t& other) const { return x * other.x + y * other.y + z * other.z; }
        vector3_t cross(const vector3_t& other) const
        {
            return {
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            };
        }
        vector3_t normalized() const
        {
            float len = length();
            if (len == 0.f) return {};
            return { x / len, y / len, z / len };
        }
    };
    struct vector4_t
    {
        float x{}, y{}, z{}, w{};
        vector4_t() = default;
        vector4_t(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    };
    struct matrix4_t
    {
        float m[4][4]{};
        vector3_t get_position() const { return { m[3][0], m[3][1], m[3][2] }; }
        vector3_t get_forward() const { return { m[2][0], m[2][1], m[2][2] }; }
        vector3_t get_right()   const { return { m[0][0], m[0][1], m[0][2] }; }
        vector3_t get_up()      const { return { m[1][0], m[1][1], m[1][2] }; }
    };
    inline vector2_t w2s(const vector3_t& world, const matrix4_t& viewmatrix, const vector2_t& dimensions, float offset_x = 0.f, float offset_y = 0.f)
    {
        vector4_t q;
        q.x = (world.x * viewmatrix.m[0][0]) + (world.y * viewmatrix.m[0][1]) + (world.z * viewmatrix.m[0][2]) + viewmatrix.m[0][3];
        q.y = (world.x * viewmatrix.m[1][0]) + (world.y * viewmatrix.m[1][1]) + (world.z * viewmatrix.m[1][2]) + viewmatrix.m[1][3];
        q.z = (world.x * viewmatrix.m[2][0]) + (world.y * viewmatrix.m[2][1]) + (world.z * viewmatrix.m[2][2]) + viewmatrix.m[2][3];
        q.w = (world.x * viewmatrix.m[3][0]) + (world.y * viewmatrix.m[3][1]) + (world.z * viewmatrix.m[3][2]) + viewmatrix.m[3][3];
        if (q.w < 0.1f)
            return { -1.f, -1.f };
        float inv_w = 1.0f / q.w;
        vector3_t ndc;
        ndc.x = q.x * inv_w;
        ndc.y = q.y * inv_w;
        ndc.z = q.z * inv_w;
        return
        {
            ((dimensions.x / 2.0f) * ndc.x + (dimensions.x / 2.0f)) + offset_x,
            (-(dimensions.y / 2.0f) * ndc.y + (dimensions.y / 2.0f)) + offset_y
        };
    }
    using address_t = std::uintptr_t;
}

