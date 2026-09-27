#include <iostream>
#include <cassert>
#include "rasterizer/math/vector2.h"
#include "rasterizer/math/vector3.h"
#include "rasterizer/math/matrix3.h"
#include "rasterizer/math/color.h"

int main() {
    using namespace rasterizer;

    // Test Vector2
    Vector2 v1(1.0f, 2.0f);
    Vector2 v2(3.0f, 4.0f);
    Vector2 v3 = v1 + v2;
    assert(v3.x == 4.0f && v3.y == 6.0f);

    // Test Matrix3 & Vector3 multiplication (Identity)
    Matrix3 identity;
    Vector3 vec(5.0f, 6.0f, 1.0f);
    Vector3 res = identity * vec;
    assert(res.x == 5.0f && res.y == 6.0f && res.z == 1.0f);

    // Test Color
    Color col(255, 128, 0, 255);
    assert(col.r == 255 && col.g == 128 && col.b == 0 && col.a == 255);

    std::cout << "All math tests passed successfully!\n";
    return 0;
}