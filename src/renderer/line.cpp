#include "rasterizer/renderer/line.h"
#include <cmath>
#include <algorithm>

namespace rasterizer {
    void DrawLine(Rasterizer& rasterizer, const Vector2& p0, const Vector2& p1, const Color& color) {
        int x0 = static_cast<int>(p0.x);
        int y0 = static_cast<int>(p0.y);
        int x1 = static_cast<int>(p1.x);
        int y1 = static_cast<int>(p1.y);

        int dx = std::abs(x1-x0);
        int dy = std::abs(y1-y0);
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            rasterizer.DrawPoint(x0,y0,color);
            if(x0 == x1 && y0 == y1) break;
            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x0 += sx; 
            }
            if (e2 < dx) {
                err += dx;
                y0 += sy;
            }
        }
    }
}
