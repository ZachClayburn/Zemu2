#include "Screen.h"

#include <SDL2/SDL.h>
#include <stdexcept>

Screen::Screen() {
    window = SDL_CreateWindow(
      "TITLE",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      160,
      144,
      SDL_WINDOW_INPUT_FOCUS);
    if (window == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (window == nullptr) {
        throw std::runtime_error(SDL_GetError());
    }
    
    texture = SDL_CreateTexture(renderer,
      SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, 160, 144);
    
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
