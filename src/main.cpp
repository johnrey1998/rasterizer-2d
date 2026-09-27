#include "rasterizer/core/core.h"
#include "rasterizer/platform/platform.h"
#include "rasterizer/renderer/rasterizer.h"
#include "rasterizer/renderer/line.h"

int main() {
    const int width = 800;
    const int height = 600;

    rasterizer::Canvas canvas(width, height);
    rasterizer::Window window("Rasterizer 2D - Line Test", width, height);
    rasterizer::Rasterizer rasterizer(canvas);

    // Clear to dark background
    rasterizer.Clear({15, 15, 20, 255});

    // Draw some test lines (X across the screen and a bounding box)
    rasterizer::DrawLine(rasterizer, {0.0f, 0.0f}, {static_cast<float>(width), static_cast<float>(height)}, {255, 0, 0, 255});
    rasterizer::DrawLine(rasterizer, {0.0f, static_cast<float>(height)}, {static_cast<float>(width), 0.0f}, {0, 255, 0, 255});
    rasterizer::DrawLine(rasterizer, {100.0f, 100.0f}, {700.0f, 100.0f}, {255, 255, 255, 255});
    rasterizer::DrawLine(rasterizer, {700.0f, 100.0f}, {700.0f, 500.0f}, {255, 255, 255, 255});
    rasterizer::DrawLine(rasterizer, {700.0f, 500.0f}, {100.0f, 500.0f}, {255, 255, 255, 255});
    rasterizer::DrawLine(rasterizer, {100.0f, 500.0f}, {100.0f, 100.0f}, {255, 255, 255, 255});

    while (window.ProcessEvents()) {
        window.Present(canvas);
    }

    return 0;
}