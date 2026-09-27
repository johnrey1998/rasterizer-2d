#pragma once

namespace rasterizer {
    struct Vector3 {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        Vector3() = default;
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

        Vector3 operator+(const Vector3& o) const { return {x + o.x, y + o.y, z + o.z}; }
        Vector3 operator-(const Vector3& o) const { return {x - o.x, y - o.y, z - o.z}; }
        Vector3 operator*(float s) const { return {x * s, y * s, z * s}; }
    };
}
