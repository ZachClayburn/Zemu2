//
// Created by zach on 5/2/20.
//

#ifndef ZEMU2_GAMEBOY_H
#define ZEMU2_GAMEBOY_H

#include <array>
#include <memory>
#include "Pixel.h"
#include "ScreenConstants.h"

class ReadWriteDevice;
class BootRom;
class IRamBank;
class PPU;

class GameBoy
{
  public:
    explicit GameBoy(std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer);
  private:
    
    static const size_t NUM_DEVICES = 4;
    std::array<std::shared_ptr<ReadWriteDevice>, NUM_DEVICES> devices;
    
    std::shared_ptr<BootRom> bootRom;
    std::shared_ptr<IRamBank> wRam;
    std::shared_ptr<IRamBank> hRam;
    
    std::shared_ptr<PPU> ppu;
    
};


#endif//ZEMU2_GAMEBOY_H
