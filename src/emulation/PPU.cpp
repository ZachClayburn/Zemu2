#include "PPU.h"

#include <utility>

#include "spdlog/spdlog.h"

#include "RamBank.h"
#include "BasicRegister.h"
#include "Pallet.h"
#include "LCDCRegister.h"
#include "STATRegister.h"

PPU::PPU(std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer, void (*screenCallback)())
  : buffer(std::move(screenBuffer)),
    updateScreen(screenCallback),
    vRam(std::make_shared<RamBank>(8 * 1024, 0x8000U)),
    BGP(std::make_shared<Pallet>(BGP_ADDR)),
    OBP0(std::make_shared<Pallet>(OBP0_ADDR)),
    OBP1(std::make_shared<Pallet>(OBP1_ADDR)),
    LCDC(std::make_shared<LCDCRegister>(LCDC_ADDR)),
    STAT(std::make_shared<STATRegister>(STAT_ADDR)),
    SCY(std::make_shared<BasicRegister>(SCY_ADDR)),
    SCX(std::make_shared<BasicRegister>(SCX_ADDR)),
    LY(std::make_shared<BasicRegister>(LY_ADDR)),
    LYC(std::make_shared<BasicRegister>(LYC_ADDR)),
    WY(std::make_shared<BasicRegister>(WY_ADDR)),
    WX(std::make_shared<BasicRegister>(WX_ADDR)),
    DMA(std::make_shared<BasicRegister>(DMA_ADDR)) {
    spdlog::info("PPU Constructed");
}

std::shared_ptr<ReadWriteDevice> PPU::getVRam() const {
    return vRam;
}

std::shared_ptr<ReadWriteDevice> PPU::getBgp() const {
    return BGP;
}

std::shared_ptr<ReadWriteDevice> PPU::getObp0() const {
    return OBP0;
}

std::shared_ptr<ReadWriteDevice> PPU::getObp1() const {
    return OBP1;
}

std::shared_ptr<ReadWriteDevice> PPU::getLcdc() const {
    return LCDC;
}

std::shared_ptr<ReadWriteDevice> PPU::getStat() const {
    return STAT;
}

std::shared_ptr<ReadWriteDevice> PPU::getScy() const {
    return SCY;
}

std::shared_ptr<ReadWriteDevice> PPU::getScx() const {
    return SCX;
}

std::shared_ptr<ReadWriteDevice> PPU::getLy() const {
    return LY;
}

std::shared_ptr<ReadWriteDevice> PPU::getLyc() const {
    return LYC;
}

std::shared_ptr<ReadWriteDevice> PPU::getWy() const {
    return WY;
}

std::shared_ptr<ReadWriteDevice> PPU::getWx() const {
    return WX;
}

std::shared_ptr<ReadWriteDevice> PPU::getDma() const {
    return DMA;
}
