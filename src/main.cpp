#include "rasterizer/core/core.h"
#include "rasterizer/platform/platform.h"
#include "rasterizer/renderer/rasterizer.h"
#include "rasterizer/renderer/line.h"
#include "rasterizer/renderer/triangle.h"

int main() {
    const int width = 800;
    const int height = 600;

    rasterizer::Canvas canvas(width, height);
    rasterizer::Window window("Rasterizer 2D - Triangle Test", width, height);
    rasterizer::Rasterizer rasterizer(canvas);

    // Clear to dark background
    rasterizer.Clear({15, 15, 20, 255});

    // Draw a filled triangle
    rasterizer::DrawTriangle(rasterizer, {300.0f, 150.0f}, {200.0f, 450.0f}, {600.0f, 450.0f}, {255, 165, 0, 255});

    // Draw outline around it
    rasterizer::DrawLine(rasterizer, {400.0f, 150.0f}, {200.0f, 450.0f}, {255, 255, 255, 255});
    rasterizer::DrawLine(rasterizer, {200.0f, 450.0f}, {600.0f, 450.0f}, {255, 255, 255, 255});
    rasterizer::DrawLine(rasterizer, {600.0f, 450.0f}, {400.0f, 150.0f}, {255, 255, 255, 255});

    while (window.ProcessEvents()) {
        window.Present(canvas);
    }

    return 0;
}