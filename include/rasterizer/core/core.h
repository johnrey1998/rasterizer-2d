#pragma once

#include <vector>
#include "rasterizer/math/color.h"

namespace rasterizer {
    class Canvas {
    public:
        Canvas(int width, int height);
        int GetWidth() const;
        int GetHeight() const;
        void SetPixel(int x, int y, const Color& color);
        const std::vector<Color>& GetPixels() const;
    private:
        int width;
        int height;
        std::vector<Color> pixels;
    };
}
