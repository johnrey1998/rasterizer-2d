#include "rasterizer/platform/platform.h"
#include "rasterizer/core/core.h"
#include <SDL3/SDL.h>

namespace rasterizer {
    Window::Window(const char* title, int w, int h) : width(w), height(h) {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow(title, width, height, 0);
        renderer = SDL_CreateRenderer(window, nullptr);
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    }

    Window::~Window() {
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    bool Window::ProcessEvents() { 
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                return false;
            }
        }
        return true; 
    }

    void Window::Present(const Canvas& canvas) {
        SDL_UpdateTexture(texture, nullptr, canvas.GetPixels().data(), width * sizeof(Color));
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }
}
