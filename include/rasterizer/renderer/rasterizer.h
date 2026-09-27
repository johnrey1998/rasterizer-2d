#pragma once

#include "rasterizer/math/vector2.h"
#include "rasterizer/math/color.h"

namespace rasterizer {
    class Canvas;

    class Rasterizer {
    public:
        explicit Rasterizer(Canvas& canvas);
        
        void DrawPoint(int x, int y, const Color& color);
        void Clear(const Color& color);

    
    private:
        Canvas& canvas;
    };
}
