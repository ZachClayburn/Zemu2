#ifndef ZEMU2_PPU_H
#define ZEMU2_PPU_H

#include <memory>
#include <array>
#include "Pixel.h"
#include "ScreenConstants.h"

class AbstractRamBank;
class BasicRegister;
class Pallet;
class LCDCRegister;
class STATRegister;

class PPU
{
  public:
    explicit PPU(std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer, void (*screenCallback)());

  private:
    std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> buffer;
    void (*updateScreen)();

    std::shared_ptr<AbstractRamBank> vRam;
    
    std::shared_ptr<Pallet> BGP;
    std::shared_ptr<Pallet> OBP0;
    std::shared_ptr<Pallet> OBP1;
    
    std::shared_ptr<LCDCRegister> LCDC;
    std::shared_ptr<STATRegister> STAT;
    std::shared_ptr<BasicRegister> SCY;
    std::shared_ptr<BasicRegister> SCX;
    std::shared_ptr<BasicRegister> LY;
    std::shared_ptr<BasicRegister> LYC;
    std::shared_ptr<BasicRegister> WY;
    std::shared_ptr<BasicRegister> WX;
    std::shared_ptr<BasicRegister> DMA;
    
    static const constexpr uint16_t BGP_ADDR{ 0xFF47U };
    static const constexpr uint16_t OBP0_ADDR{ 0xFF48U };
    static const constexpr uint16_t OBP1_ADDR{ 0xFF49U };
    
    static const constexpr uint16_t LCDC_ADDR{ 0xFF40U };
    static const constexpr uint16_t STAT_ADDR{ 0xFF41U };
    static const constexpr uint16_t SCY_ADDR{ 0xFF42U };
    static const constexpr uint16_t SCX_ADDR{ 0xFF43U };
    static const constexpr uint16_t LY_ADDR{ 0xFF44U };
    static const constexpr uint16_t LYC_ADDR{ 0xFF45U };
    static const constexpr uint16_t WY_ADDR{ 0xFF4AU };
    static const constexpr uint16_t WX_ADDR{ 0xFF4BU };
    static const constexpr uint16_t DMA_ADDR{ 0xFF46U };
};


#endif//ZEMU2_PPU_H
