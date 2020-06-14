//
// Created by zach on 5/2/20.
//

#ifndef ZEMU2_GAMEBOY_H
#define ZEMU2_GAMEBOY_H

#include <memory>
#include "Pixel.h"
#include "ScreenConstants.h"

class Bus;

class GameBoy
{
  public:
    GameBoy(const std::shared_ptr<std::array<Pixel, PIXEL_COUNT>>& screenBuffer, void (*screenCallback)());
    ~GameBoy();
    
    GameBoy(const GameBoy&) = delete;
    GameBoy& operator=(const GameBoy&) = delete;
    GameBoy(const GameBoy&&) = delete;
    GameBoy& operator=(const GameBoy&&) = delete;
    
    void clock();
  
  private:
    std::unique_ptr<Bus> bus;
    
};


#endif//ZEMU2_GAMEBOY_H
