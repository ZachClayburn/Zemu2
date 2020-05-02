#ifndef ZEMU2_PPU_H
#define ZEMU2_PPU_H

#include <memory>
#include <array>
#include "Pixel.h"
#include "ScreenConstants.h"

class IRamBank;

class PPU
{
  public:
    explicit PPU(std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer);

  private:
    std::shared_ptr<IRamBank> vRam;
    std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> buffer;
};


#endif//ZEMU2_PPU_H
