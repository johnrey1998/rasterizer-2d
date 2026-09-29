#include "rasterizer/core/core.h"
#include "rasterizer/platform/platform.h"
#include "rasterizer/renderer/rasterizer.h"
#include "rasterizer/renderer/triangle.h"
#include "rasterizer/renderer/texture.h"
#include "rasterizer/math/vector2.h"
#include "rasterizer/math/vector3.h"
#include "rasterizer/math/matrix3.h"
#include <cmath>
#include <vector>
#include <algorithm>

int main() {
    const int width = 800;
    const int height = 600;

    rasterizer::Canvas canvas(width, height);
    rasterizer::Window window("Rasterizer 2D - Press [1] Triangle, [2] Cube, [3] Sphere", width, height);
    rasterizer::Rasterizer rasterizer(canvas);

    // --- Scene 1 Data: Textured Triangle ---
    rasterizer::Texture texture(64, 64);
    for (int ty = 0; ty < 64; ++ty) {
        for (int tx = 0; tx < 64; ++tx) {
            bool checker = ((tx / 8) + (ty / 8)) % 2 == 0;
            rasterizer::Color col = checker ? rasterizer::Color{255, 0, 220, 255} : rasterizer::Color{0, 0, 0, 255};
            texture.SetPixel(tx, ty, col);
        }
    }
    rasterizer::Vector2 localP0{0.0f, -80.0f};
    rasterizer::Vector2 localP1{-70.0f, 70.0f};
    rasterizer::Vector2 localP2{70.0f, 70.0f};
    float triAngle = 0.0f;

    // --- Scene 2 Data: 3D Cube ---
    float s = 60.0f;
    rasterizer::Vector3 cubeVertices[8] = {
        {-s, -s, -s}, { s, -s, -s}, { s,  s, -s}, {-s,  s, -s},
        {-s, -s,  s}, { s, -s,  s}, { s,  s,  s}, {-s,  s,  s}
    };

    struct CubeFace { int i0, i1, i2; rasterizer::Color color; };
    CubeFace cubeFaces[12] = {
        {0, 1, 2, {255, 90, 90, 255}}, {0, 2, 3, {255, 90, 90, 255}},
        {5, 4, 7, {90, 255, 90, 255}}, {5, 7, 6, {90, 255, 90, 255}},
        {4, 0, 3, {90, 90, 255, 255}}, {4, 3, 7, {90, 90, 255, 255}},
        {1, 5, 6, {255, 255, 90, 255}}, {1, 6, 2, {255, 255, 90, 255}},
        {3, 2, 6, {255, 90, 255, 255}}, {3, 6, 7, {255, 90, 255, 255}},
        {4, 5, 1, {90, 255, 255, 255}}, {4, 1, 0, {90, 255, 255, 255}}
    };
    float cubeAngleX = 0.0f;
    float cubeAngleY = 0.0f;

    // --- Scene 3 Data: 3D Sphere ---
    int lats = 12;
    int longs = 16;
    float radius = 120.0f;
    struct SphereVertex { rasterizer::Vector3 pos; rasterizer::Vector2 uv; };
    struct SphereTriangle { int i0, i1, i2; };
    std::vector<SphereVertex> sphereVerts;
    std::vector<SphereTriangle> sphereTris;

    for (int i = 0; i <= lats; ++i) {
        float theta = i * 3.14159265f / lats;
        float sinTheta = std::sin(theta);
        float cosTheta = std::cos(theta);
        for (int j = 0; j <= longs; ++j) {
            float phi = j * 2.0f * 3.14159265f / longs;
            float x = radius * sinTheta * std::cos(phi);
            float y = radius * cosTheta;
            float z = radius * sinTheta * std::sin(phi);
            sphereVerts.push_back({ {x, y, z}, {(float)j / longs, (float)i / lats} });
        }
    }
    // Correcting push_back for sphere vertices
    sphereVerts.clear();
    for (int i = 0; i <= lats; ++i) {
        float theta = i * 3.14159265f / lats;
        float sinTheta = std::sin(theta);
        float cosTheta = std::cos(theta);
        for (int j = 0; j <= longs; ++j) {
            float phi = j * 2.0f * 3.14159265f / longs;
            float x = radius * sinTheta * std::cos(phi);
            float y = radius * cosTheta;
            float z = radius * sinTheta * std::sin(phi);
            sphereVerts.push_back({ {x, y, z}, {(float)j / longs, (float)i / lats} });
        }
    }
    for (int i = 0; i < lats; ++i) {
        for (int j = 0; j < longs; ++j) {
            int first = i * (longs + 1) + j;
            int second = first + longs + 1;
            sphereTris.push_back({first, second, first + 1});
            sphereTris.push_back({second, second + 1, first + 1});
        }
    }
    float sphereAngle = 0.0f;

    while (window.ProcessEvents()) {
        rasterizer.Clear({15, 15, 20, 255});
        int scene = window.GetActiveScene();

        if (scene == 1) {
            rasterizer::Matrix3 transform = 
                rasterizer::Matrix3::Translation(400.0f, 300.0f) * 
                rasterizer::Matrix3::Rotation(triAngle);

            auto t0 = transform * rasterizer::Vector3{localP0.x, localP0.y, 1.0f};
            auto t1 = transform * rasterizer::Vector3{localP1.x, localP1.y, 1.0f};
            auto t2 = transform * rasterizer::Vector3{localP2.x, localP2.y, 1.0f};

            rasterizer::DrawTriangle(
                rasterizer,
                {t0.x, t0.y}, {0.5f, 0.0f},
                {t1.x, t1.y}, {0.0f, 1.0f},
                {t2.x, t2.y}, {1.0f, 1.0f},
                texture
            );
            triAngle += 0.02f;
        } 
        else if (scene == 2) {
            float cx = std::cos(cubeAngleX);
            float sx = std::sin(cubeAngleX);
            float cy = std::cos(cubeAngleY);
            float sy = std::sin(cubeAngleY);

            rasterizer::Vector2 projected[8];
            float depths[8];

            for (int i = 0; i < 8; ++i) {
                rasterizer::Vector3 v = cubeVertices[i];
                float x1 = v.x * cy + v.z * sy;
                float y1 = v.y;
                float z1 = -v.x * sy + v.z * cy;

                projected[i] = {x1 + 400.0f, y1 * cx - z1 * sx + 300.0f};
                depths[i] = y1 * sx + z1 * cx;
            }

            struct SortedFace { int faceIndex; float avgZ; };
            std::vector<SortedFace> sortedFaces(12);
            for (int i = 0; i < 12; ++i) {
                const auto& f = cubeFaces[i];
                sortedFaces[i] = {i, (depths[f.i0] + depths[f.i1] + depths[f.i2]) / 3.0f};
            }

            std::sort(sortedFaces.begin(), sortedFaces.end(), [](auto& a, auto& b) {
                return a.avgZ < b.avgZ;
            });

            for (const auto& sf : sortedFaces) {
                const auto& f = cubeFaces[sf.faceIndex];
                rasterizer::Texture solidTex(1, 1);
                solidTex.SetPixel(0, 0, f.color);
                rasterizer::DrawTriangle(
                    rasterizer,
                    projected[f.i0], {0.0f, 0.0f},
                    projected[f.i1], {0.0f, 0.0f},
                    projected[f.i2], {0.0f, 0.0f},
                    solidTex
                );
            }

            cubeAngleX += 0.015f;
            cubeAngleY += 0.02f;
        }
        else if (scene == 3) {
            float cy = std::cos(sphereAngle);
            float sy = std::sin(sphereAngle);

            std::vector<rasterizer::Vector2> projected(sphereVerts.size());
            std::vector<float> depths(sphereVerts.size());

            for (size_t i = 0; i < sphereVerts.size(); ++i) {
                auto v = sphereVerts[i].pos;
                float x1 = v.x * cy + v.z * sy;
                float y1 = v.y;
                float z1 = -v.x * sy + v.z * cy;

                projected[i] = {x1 + 400.0f, y1 + 300.0f};
                depths[i] = z1;
            }

            struct SortedTri { size_t triIdx; float avgZ; };
            std::vector<SortedTri> sortedTris(sphereTris.size());
            for (size_t i = 0; i < sphereTris.size(); ++i) {
                const auto& t = sphereTris[i];
                float az = (depths[t.i0] + depths[t.i1] + depths[t.i2]) / 3.0f;
                sortedTris[i] = {i, az};
            }

            std::sort(sortedTris.begin(), sortedTris.end(), [](auto& a, auto& b) {
                return a.avgZ < b.avgZ;
            });

            for (const auto& st : sortedTris) {
                const auto& t = sphereTris[st.triIdx];
                rasterizer::DrawTriangle(
                    rasterizer,
                    projected[t.i0], sphereVerts[t.i0].uv,
                    projected[t.i1], sphereVerts[t.i1].uv,
                    projected[t.i2], sphereVerts[t.i2].uv,
                    texture
                );
            }

            sphereAngle += 0.02f;
        }

        window.Present(canvas);
    }

    return 0;
}