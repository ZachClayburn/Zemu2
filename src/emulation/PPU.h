#ifndef ZEMU2_PPU_H
#define ZEMU2_PPU_H

#include <memory>
#include <array>
#include "Pixel.h"
#include "ScreenConstants.h"

class AbstractRamBank;

class PPU
{
  public:
    explicit PPU(std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer, void (*screenCallback)());

  private:
    std::shared_ptr<AbstractRamBank> vRam;
    std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> buffer;

    void (*updateScreen)();
};


#endif//ZEMU2_PPU_H
