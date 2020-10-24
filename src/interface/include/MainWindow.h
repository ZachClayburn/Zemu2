//
// Created by zach on 4/30/20.
//

#ifndef ZEMU2_MAINWINDOW_H
#define ZEMU2_MAINWINDOW_H

#include <cstdint>
#include <string>
#include <array>
#include <memory>
#include "Pixel.h"
#include "ScreenConstants.h"

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class MainWindow
{
  public:
    MainWindow(MainWindow const& screen) = delete;
    MainWindow(MainWindow const&& screen) = delete;
    void operator=(MainWindow const& screen) = delete;
    void operator=(MainWindow const&& screen) = delete;

    static void updateDisplay();
    [[nodiscard]] std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> getScreenBuffer();
    static MainWindow& get();

    // TODO Remove this when not needed for debugging
    static void pause(uint32_t ms);

  private:
    explicit MainWindow();
    virtual ~MainWindow();

    SDL_Window* window{ nullptr };
    SDL_Renderer* renderer{ nullptr };
    SDL_Texture* texture{ nullptr };

    std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer;

    static const int SCALE = 5;
};


#endif// ZEMU2_MAINWINDOW_H
