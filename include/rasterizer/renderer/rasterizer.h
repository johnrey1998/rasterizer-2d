#pragma once

#include "rasterizer/math/vector2.h"
#include "rasterizer/math/color.h"

namespace rasterizer {
    class Rasterizer {
    public:
        Rasterizer(int width, int height);
        void Clear(const Color& color);
    };
}
