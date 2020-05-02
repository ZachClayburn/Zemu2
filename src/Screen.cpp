#include "Screen.h"

#include <SDL2/SDL.h>
#include <stdexcept>
#include <spdlog/spdlog.h>

Screen::Screen() {
    
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(SDL_GetError());
    }
    
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    
    window = SDL_CreateWindow(
      "Zemu",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCALE * GAMEBOY_WIDTH,
      SCALE * GAMEBOY_HEIGHT,
      SDL_WINDOW_INPUT_FOCUS);
    if (window == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (window == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
    SDL_RenderSetLogicalSize(renderer, GAMEBOY_WIDTH, GAMEBOY_HEIGHT);
    
    texture = SDL_CreateTexture(renderer,
      SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, GAMEBOY_WIDTH, GAMEBOY_HEIGHT);
    
    if (window == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
}
Screen::~Screen() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
}
void Screen::pause(uint32_t ms) {
    SDL_Delay(ms);
}
void Screen::updateDisplay(const std::array<Pixel, PIXEL_COUNT> &buffer) {
    SDL_UpdateTexture(texture, nullptr, buffer.data(), GAMEBOY_WIDTH * sizeof(uint8_t) * 3);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}
Screen &Screen::get() {
    static Screen instance;
    return instance;
}
