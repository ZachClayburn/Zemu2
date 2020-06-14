#ifndef ZEMU2_BUS_H
#define ZEMU2_BUS_H

#include <memory>
#include <array>

#include "ReadWriteDevice.h"
#include "PPU.h"
#include "BootRom.h"
#include "CPU.h"

class Bus
{
  public:
    Bus(std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer, void (*screenCallback)());
    void clock();

  private:
    static const size_t NUM_DEVICES = 17;
    std::array<std::shared_ptr<ReadWriteDevice>, NUM_DEVICES> devices;
    
    PPU ppu;
    CPU cpu;
    
    std::shared_ptr<BootRom> bootRom;
    std::shared_ptr<AbstractRamBank> wRam;
    std::shared_ptr<AbstractRamBank> hRam;
    
};


#endif//ZEMU2_BUS_H
