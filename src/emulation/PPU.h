#ifndef ZEMU2_PPU_H
#define ZEMU2_PPU_H

#include <memory>
#include "Pixel.h"
#include "ScreenConstants.h"

class AbstractRamBank;
class BasicRegister;
class Pallet;
class LCDCRegister;
class STATRegister;
class ReadWriteDevice;

class PPU
{
  public:
    PPU(std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer, void (*screenCallback)());

    void clock();

    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getVRam() const;
    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getBgp() const;
    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getObp0() const;
    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getObp1() const;
    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getLcdc() const;
    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getStat() const;
    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getScy() const;
    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getScx() const;
    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getLy() const;
    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getLyc() const;
    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getWy() const;
    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getWx() const;
    [[nodiscard]] std::shared_ptr<ReadWriteDevice> getDma() const;

  private:
    std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> buffer;
    void (*updateScreen)();

    int cycleClocks{ 0 };

    void H_BLANK();
    void V_BLANK();
    void OAM_SEARCH();
    void OAM_TRANSFER();

    void drawScanLine();
    void moveScanLine();

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
};


#endif// ZEMU2_PPU_H
