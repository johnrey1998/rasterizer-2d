#include "rasterizer/renderer/rasterizer.h"
#include "rasterizer/core/core.h"

namespace rasterizer {
    Rasterizer::Rasterizer(Canvas& canvas) : canvas(canvas) {}
    void Rasterizer::Clear(const Color& color) {
        int width = canvas.GetWidth();
        int height = canvas.GetHeight();
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                canvas.SetPixel(x, y, color);    
            }
            
        }
    }

    void Rasterizer::DrawPoint(int x, int y, const Color& color) {
        canvas.SetPixel(x, y, color);
    }
}
