#include "rasterizer/core/core.h"
#include "rasterizer/platform/platform.h"

int main() {
    const int width = 800;
    const int height = 600;

    rasterizer::Canvas canvas(width, height);
    rasterizer::Window window("Rasterizer 2D", width, height);

    // Draw a simple red diagonal line / gradient across the canvas
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            rasterizer::Color col{
                static_cast<unsigned char>((x * 255) / width),
                static_cast<unsigned char>((y * 255) / height),
                128,
                255
            };
            canvas.SetPixel(x, y, col);
        }
    }

    while (window.ProcessEvents()) {
        window.Present(canvas);
    }

    return 0;
}