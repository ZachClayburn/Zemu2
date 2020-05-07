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
class AbstractRamBank;
class PPU;

class GameBoy
{
  public:
    GameBoy(std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer, void (*screenCallback)());
  private:
    
    static const size_t NUM_DEVICES = 17;
    std::array<std::shared_ptr<ReadWriteDevice>, NUM_DEVICES> devices;
    
    std::shared_ptr<PPU> ppu;
    
    std::shared_ptr<BootRom> bootRom;
    std::shared_ptr<AbstractRamBank> wRam;
    std::shared_ptr<AbstractRamBank> hRam;
    
    
};


#endif//ZEMU2_GAMEBOY_H
