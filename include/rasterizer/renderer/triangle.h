#pragma once

#include "rasterizer/math/vector2.h"
#include "rasterizer/math/color.h"
#include "rasterizer/renderer/rasterizer.h"
#include "rasterizer/renderer/texture.h"

namespace rasterizer {
    void DrawTriangle(Rasterizer& rasterizer, 
                      const Vector2& p0, const Vector2& uv0, 
                      const Vector2& p1, const Vector2& uv1, 
                      const Vector2& p2, const Vector2& uv2, 
                      const Texture& texture);
}
