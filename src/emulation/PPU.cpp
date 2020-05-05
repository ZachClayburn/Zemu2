#include "PPU.h"

#include <utility>
#include "RamBank.h"

PPU::PPU(std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer, void (*screenCallback)())
  : vRam(std::make_shared<RamBank>(8 * 1024, 0x8000U)),
    buffer(std::move(screenBuffer)),
    updateScreen(screenCallback) {}
