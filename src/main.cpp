#include "rasterizer/core/core.h"
#include "rasterizer/platform/platform.h"
#include "rasterizer/renderer/rasterizer.h"

int main() {
    const int width = 800;
    const int height = 600;

    rasterizer::Canvas canvas(width, height);
    rasterizer::Window window("Rasterizer 2D - Test", width, height);
    rasterizer::Rasterizer rasterizer(canvas);

    // Clear canvas to dark blue
    rasterizer.Clear({20, 30, 50, 255});

    // Draw a bright white point at the center (400, 300)
    rasterizer.DrawPoint(width / 2, height / 2, {255, 255, 255, 255});

    while (window.ProcessEvents()) {
        window.Present(canvas);
    }

    return 0;
}