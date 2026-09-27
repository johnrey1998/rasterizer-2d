#include "rasterizer/renderer/triangle.h"
#include <algorithm>
#include <cmath>

namespace rasterizer {
    static float EdgeFunction(const Vector2& a, const Vector2& b, const Vector2& p) {
        return (p.x - a.x) * (b.y - a.y) - (p.y - a.y) * (b.x - a.x);
    }


    void DrawTriangle(Rasterizer& rasterizer, const Vector2& p0, const Vector2& p1, const Vector2& p2, const Color& color) {

        int minX = static_cast<int>(std::floor(std::min({p0.x, p1.x, p2.x})));
        int maxX = static_cast<int>(std::ceil(std::max({p0.x, p1.x, p2.x})));
        int minY = static_cast<int>(std::floor(std::min({p0.y, p1.y, p2.y})));
        int maxY = static_cast<int>(std::ceil(std::max({p0.y, p1.y, p2.y})));

        float area = EdgeFunction(p0, p1, p2);
        if (std::abs(area) < 1e-5f) return;

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x){
                Vector2 p{static_cast<float>(x) + 0.5f, static_cast<float>(y) + 0.5f};

                float w0 = EdgeFunction(p1, p2, p);
                float w1 = EdgeFunction(p2,p0,p);
                float w2 = EdgeFunction(p0, p1, p);

                if(w0 >= 0.0f && w1 >= 0.0f && w2 >= 0.0f) {
                    rasterizer.DrawPoint(x,y,color);
                }
            }
        }

    }
}
