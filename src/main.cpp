#include "rasterizer/core/core.h"
#include "rasterizer/platform/platform.h"
#include "rasterizer/renderer/rasterizer.h"
#include "rasterizer/renderer/line.h"
#include "rasterizer/renderer/triangle.h"
#include "rasterizer/renderer/texture.h"

int main() {
    const int width = 800;
    const int height = 600;

    rasterizer::Canvas canvas(width, height);
    rasterizer::Window window("Rasterizer 2D - Comprehensive Test", width, height);
    rasterizer::Rasterizer rasterizer(canvas);

    // Create a 64x64 checkerboard texture
    rasterizer::Texture texture(64, 64);
    for (int ty = 0; ty < 64; ++ty) {
        for (int tx = 0; tx < 64; ++tx) {
            bool checker = ((tx / 8) + (ty / 8)) % 2 == 0;
            rasterizer::Color col = checker ? rasterizer::Color{255, 255, 255, 255} : rasterizer::Color{50, 50, 50, 255};
            texture.SetPixel(tx, ty, col);
        }
    }

    // Clear background
    rasterizer.Clear({15, 15, 20, 255});

    // 1. Test Textured Triangle on the left
    rasterizer::DrawTriangle(
        rasterizer,
        {200.0f, 100.0f}, {0.5f, 0.0f},
        {100.0f, 300.0f}, {0.0f, 1.0f},
        {300.0f, 300.0f}, {1.0f, 1.0f},
        texture
    );

    // 2. Test Solid Triangle on the right using a 1x1 texture
    rasterizer::Texture solidTex(1, 1);
    solidTex.SetPixel(0, 0, {255, 105, 180, 255});
    rasterizer::DrawTriangle(
        rasterizer,
        {600.0f, 100.0f}, {0.0f, 0.0f},
        {500.0f, 300.0f}, {0.0f, 0.0f},
        {700.0f, 300.0f}, {0.0f, 0.0f},
        solidTex
    );

    // 3. Test Lines (Grid / Crosshairs at bottom)
    rasterizer::DrawLine(rasterizer, {100.0f, 400.0f}, {700.0f, 400.0f}, {0, 255, 255, 255});
    rasterizer::DrawLine(rasterizer, {400.0f, 400.0f}, {400.0f, 550.0f}, {0, 255, 255, 255});

    // 4. Test Points
    for (int i = 0; i < 10; ++i) {
        rasterizer.DrawPoint(350 + i * 10, 500, {255, 255, 0, 255});
    }

    while (window.ProcessEvents()) {
        window.Present(canvas);
    }

    return 0;
}