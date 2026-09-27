#pragma once

#include "rasterizer/math/vector3.h"

namespace rasterizer {
    struct Matrix3 {
        float m[3][3] = { 
            {1.0f, 0.0f, 0.0f}, 
            {0.0f, 1.0f, 0.0f}, 
            {0.0f, 0.0f, 1.0f} 
        };

        Matrix3() = default;

        Vector3 operator*(const Vector3& v) const {
            return {
                m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
                m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
                m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
            };
        }
    };
}
