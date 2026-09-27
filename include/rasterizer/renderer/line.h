#pragma once

#include "rasterizer/math/vector2.h"
#include "rasterizer/math/color.h"
#include "rasterizer/renderer/rasterizer.h"

namespace rasterizer {
    void DrawLine(Rasterizer& ras, const Vector2& p0, const Vector2& p1, const Color& color);
}
