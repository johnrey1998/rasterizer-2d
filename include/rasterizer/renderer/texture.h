#pragma once

#include <vector>
#include "rasterizer/math/color.h"

namespace rasterizer {
    class Texture {
    public:
        Texture(int width, int height);
        int GetWidth() const;
        int GetHeight() const;
        void SetPixel(int x, int y, const Color& color);
        Color GetPixel(int x, int y) const;
        Color Sample(float u, float v) const;

    private:
        int width;
        int height;
        std::vector<Color> pixels;

    };
}
