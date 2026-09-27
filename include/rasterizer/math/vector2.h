#pragma once

#include <cmath>

namespace rasterizer {
    struct Vector2 {
        float x = 0.0f;
        float y = 0.0f;
        Vector2() = default;
        Vector2(float x, float y) : x(x), y(y) {}

        Vector2 operator+(const Vector2& o) const { return {x + o.x, y + o.y}; }
        Vector2 operator-(const Vector2& o) const { return {x - o.x, y - o.y}; }
        Vector2 operator*(float s) const { return {x * s, y * s }; }


    };
    
}
