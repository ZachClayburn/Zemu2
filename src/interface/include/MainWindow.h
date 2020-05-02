//
// Created by zach on 4/30/20.
//

#ifndef ZEMU2_MAINWINDOW_H
#define ZEMU2_MAINWINDOW_H

#include <cstdint>
#include <string>
#include <array>

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

struct Pixel
{
    uint8_t red{ 0 };
    uint8_t green{ 0 };
    uint8_t blue{ 0 };
};

class MainWindow
{
  public:
    MainWindow(MainWindow const &screen) = delete;
    MainWindow(MainWindow const &&screen) = delete;
    void operator=(MainWindow const &screen) = delete;
    void operator=(MainWindow const &&screen) = delete;

    static const uint16_t GAMEBOY_WIDTH = 160;
    static const uint16_t GAMEBOY_HEIGHT = 144;
    static const uint16_t PIXEL_COUNT = GAMEBOY_WIDTH * GAMEBOY_HEIGHT;

    void updateDisplay(const std::array<Pixel, PIXEL_COUNT> &buffer);
    
    static MainWindow & get();

    //TODO Remove this when not needed for debugging
    static void pause(uint32_t ms);

  private:
    explicit MainWindow();
    virtual ~MainWindow();

    SDL_Window *window{ nullptr };
    SDL_Renderer *renderer{ nullptr };
    SDL_Texture *texture{ nullptr };

    static const int SCALE = 5;
};


#endif//ZEMU2_MAINWINDOW_H
