#include "rasterizer/core/core.h"

namespace rasterizer {
    Canvas::Canvas(int w, int h) : width(w), height(h), pixels(w * h) {}

    int Canvas::GetWidth() const { return width; }
    int Canvas::GetHeight() const { return height; }

    void Canvas::SetPixel(int x, int y, const Color& color) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y * width + x] = color;
        }
    }

    const std::vector<Color>& Canvas::GetPixels() const {
        return pixels;
    }
}
