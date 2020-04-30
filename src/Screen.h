//
// Created by zach on 4/30/20.
//

#ifndef ZEMU2_SCREEN_H
#define ZEMU2_SCREEN_H

#include <cstdint>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class Screen
{
  public:
    Screen();
    virtual ~Screen();

    static void pause(uint32_t ms);

  private:
    SDL_Window *window{ nullptr };
    SDL_Renderer *renderer{ nullptr };
    SDL_Texture *texture{ nullptr };
};


#endif//ZEMU2_SCREEN_H
