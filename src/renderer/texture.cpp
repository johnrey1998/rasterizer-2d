#include "rasterizer/renderer/texture.h"
#include <algorithm>
#include <cmath>


namespace rasterizer {
    Texture::Texture(int w, int h) : width(w), height(h), pixels(w * h, Color{255,255,255,255}) {}
    int Texture::GetWidth() const { return width; }
    int Texture::GetHeight() const { return height; }

    void Texture::SetPixel(int x, int y, const Color& color) {
        if (x>=0 && x < width && y >= 0 && y < height) {
            pixels[y * width + x] = color;
        }
    }

    Color Texture::GetPixel(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) return {0,0,0,255};
        return pixels[y*width+x];
    }


    Color Texture::Sample(float u, float v) const {
        u = std::clamp(u, 0.0f, 1.0f);
        v = std::clamp(v, 0.0f, 1.0f);
        int x = static_cast<int>(u * (width-1));
        int y = static_cast<int>(v * (height-1));
        return GetPixel(x,y);
    }
}
