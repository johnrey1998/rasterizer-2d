#pragma once

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

namespace rasterizer {
    class Canvas;

    class Window {
    public:
        Window(const char* title, int width, int height);
        ~Window();

        bool ProcessEvents();
        void Present(const Canvas& canvas);
        int GetActiveScene() const { return activeScene; }

    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;
        int width;
        int height;
        int activeScene = 1;
    };
}