#pragma once

#include "rasterizer/math/vector3.h"
#include <cmath>

namespace rasterizer {
    struct Matrix3 {
        float m[3][3] = { 
            {1.0f, 0.0f, 0.0f}, 
            {0.0f, 1.0f, 0.0f}, 
            {0.0f, 0.0f, 1.0f} 
        };

        Matrix3() = default;

        // Matrix multiplication
        Matrix3 operator*(const Matrix3& o) const {
            Matrix3 res;
            for (int r = 0; r < 3; ++r) {
                for (int c = 0; c < 3; ++c) {
                    res.m[r][c] = m[r][0] * o.m[0][c] + m[r][1] * o.m[1][c] + m[r][2] * o.m[2][c];
                }
            }
            return res;
        }

        Vector3 operator*(const Vector3& v) const {
            return {
                m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
                m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
                m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
            };
        }

        static Matrix3 Translation(float dx, float dy) {
            Matrix3 mat;
            mat.m[0][2] = dx;
            mat.m[1][2] = dy;
            return mat;
        }

        static Matrix3 Rotation(float angleRadians) {
            Matrix3 mat;
            float c = std::cos(angleRadians);
            float s = std::sin(angleRadians);
            mat.m[0][0] = c;  mat.m[0][1] = -s;
            mat.m[1][0] = s;  mat.m[1][1] = c;
            return mat;
        }

        static Matrix3 Scaling(float sx, float sy) {
            Matrix3 mat;
            mat.m[0][0] = sx;
            mat.m[1][1] = sy;
            return mat;
        }
    };
}