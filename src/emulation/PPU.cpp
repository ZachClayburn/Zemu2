#include "PPU.h"

#include <utility>

#include "spdlog/spdlog.h"

#include "RamBank.h"
#include "BasicRegister.h"
#include "Pallet.h"
#include "LCDCRegister.h"
#include "STATRegister.h"
#include "ScreenConstants.h"
#include "bitUtils.h"

const constexpr uint16_t VRAM_START_ADDR{ 0x8000U };
const constexpr uint16_t BGP_ADDR{ 0xFF47U };
const constexpr uint16_t OBP0_ADDR{ 0xFF48U };
const constexpr uint16_t OBP1_ADDR{ 0xFF49U };
const constexpr uint16_t LCDC_ADDR{ 0xFF40U };
const constexpr uint16_t STAT_ADDR{ 0xFF41U };
const constexpr uint16_t SCY_ADDR{ 0xFF42U };
const constexpr uint16_t SCX_ADDR{ 0xFF43U };
const constexpr uint16_t LY_ADDR{ 0xFF44U };
const constexpr uint16_t LYC_ADDR{ 0xFF45U };
const constexpr uint16_t WY_ADDR{ 0xFF4AU };
const constexpr uint16_t WX_ADDR{ 0xFF4BU };
const constexpr uint16_t DMA_ADDR{ 0xFF46U };

PPU::PPU(std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer, void (*screenCallback)())
  : buffer(std::move(screenBuffer)), updateScreen(screenCallback),
    vRam(std::make_shared<RamBank>(8 * 1024, VRAM_START_ADDR)),
    BGP(std::make_shared<Pallet>(BGP_ADDR)), OBP0(std::make_shared<Pallet>(OBP0_ADDR)),
    OBP1(std::make_shared<Pallet>(OBP1_ADDR)), LCDC(std::make_shared<LCDCRegister>(LCDC_ADDR)),
    STAT(std::make_shared<STATRegister>(STAT_ADDR)), SCY(std::make_shared<BasicRegister>(SCY_ADDR)),
    SCX(std::make_shared<BasicRegister>(SCX_ADDR)), LY(std::make_shared<BasicRegister>(LY_ADDR)),
    LYC(std::make_shared<BasicRegister>(LYC_ADDR)), WY(std::make_shared<BasicRegister>(WY_ADDR)),
    WX(std::make_shared<BasicRegister>(WX_ADDR)), DMA(std::make_shared<BasicRegister>(DMA_ADDR)) {
    spdlog::info("PPU Constructed");
}

const constexpr int H_BLANK_CLOCKS = 204;
const constexpr int OAM_SEARCH_CLOCKS = 80;
const constexpr int OAM_TRANSFER_CLOCKS = 172;
const constexpr int VIDEO_CYCLE_CLOCKS = H_BLANK_CLOCKS + OAM_SEARCH_CLOCKS + OAM_TRANSFER_CLOCKS;
const constexpr int V_BLANK_CYCLES = 10;
const constexpr int V_BLANK_CLOCKS = VIDEO_CYCLE_CLOCKS * V_BLANK_CYCLES;

void PPU::clock() {
    if (!LCDC->displayEnable()) { return; }
    cycleClocks++;
    // TODO Properly enable/disable video memory depending on the cycle
    switch (STAT->modeFlag()) {
    case STATRegister::H_BLANK:
        H_BLANK();
        break;
    case STATRegister::V_BLANK:
        V_BLANK();
        break;
    case STATRegister::OAM_SEARCH:
        OAM_SEARCH();
        break;
    case STATRegister::OAM_TRANSFER:
        OAM_TRANSFER();
        break;
    }
}

void PPU::H_BLANK() {
    if (cycleClocks < H_BLANK_CLOCKS) { return; }
    cycleClocks = 0;

    moveScanLine();
    if (LY->getRegVal() == GAMEBOY_HEIGHT) {
        STAT->setMode(STATRegister::V_BLANK);
        // TODO Trigger appropriate interrupts
    } else {
        STAT->setMode(STATRegister::OAM_SEARCH);
        // TODO Trigger appropriate interrupts
    }
}

void PPU::V_BLANK() {
    if ((cycleClocks + 1) % VIDEO_CYCLE_CLOCKS == 0) { moveScanLine(); }
    if (cycleClocks == V_BLANK_CLOCKS) {
        cycleClocks = 0;
        STAT->setMode(STATRegister::OAM_SEARCH);
        // TODO Trigger appropriate interrupts
    }
}

void PPU::OAM_SEARCH() {
    if (cycleClocks < OAM_SEARCH_CLOCKS) { return; }
    cycleClocks = 0;
    STAT->setMode(STATRegister::OAM_TRANSFER);
}

void PPU::OAM_TRANSFER() {
    if (cycleClocks < OAM_TRANSFER_CLOCKS) { return; }

    drawScanLine();

    cycleClocks = 0;
    STAT->setMode(STATRegister::H_BLANK);

    if (STAT->hBlankInterruptEnabled()) {
        // TODO Trigger interrupt
    }
}

void PPU::drawScanLine() {
    if (LCDC->bgDisplay()) {
        // TODO Right now we are repeating a lot of work by getting the upper and lower bytes
        //     for every pixel in the line. This could be a lot more efficient if we went by
        //     tile, but the scroll values make that non-trivial. Put time into sorting this
        //     out later.
        constexpr const uint8_t TILE_WIDTH = 8;
        constexpr const uint8_t MAP_WIDTH = 32;
        constexpr const uint8_t TILE_SIZE = 16;
        constexpr const uint8_t BYTES_PER_LINE = 2;

        uint16_t tileDataStartAddr = LCDC->bgWindowTileData();
        for (int pixel = 0; pixel < GAMEBOY_WIDTH; ++pixel) {
            uint8_t xPos = pixel + SCX->getRegVal();
            uint8_t yPos = LY->getRegVal() + SCY->getRegVal();

            uint8_t tileRow = ((yPos / TILE_WIDTH) * MAP_WIDTH);
            uint8_t tileNumber = vRam->read(LCDC->bgTileMap() + tileRow + (xPos / TILE_WIDTH));
            uint8_t tileData{ 0 };
            if (tileDataStartAddr == LCDCRegister::TILE_DATA_UNSIGNED_START_ADDR) {
                tileData = tileDataStartAddr + (tileNumber * TILE_SIZE);
            } else {
                auto tileNumberSigned = static_cast<int8_t>(tileNumber);
                tileData = tileDataStartAddr + (tileNumberSigned * TILE_SIZE);
            }

            uint8_t yOffset = (yPos % TILE_WIDTH) * BYTES_PER_LINE;
            uint8_t lsbByte = vRam->read(tileData + yOffset);
            uint8_t msbByte = vRam->read(tileData + yOffset + 1);

            uint8_t colorBit = TILE_WIDTH - (xPos % TILE_WIDTH) - 1;
            uint8_t colorNumber = 0;
            if (readBit(msbByte, colorBit)) { colorNumber += 0b10; }
            if (readBit(lsbByte, colorBit)) { colorNumber += 0b01; }

            Pallet::Shade shade = (*BGP)[colorNumber];

            // TODO Make a better more reusable way to get the color
            uint8_t brightness{ 0 };
            switch (shade) {

            case Pallet::WHITE:
                brightness = 0xFF;
                break;
            case Pallet::LIGHT_GRAY:
                brightness = 0xAA;
                break;
            case Pallet::DARK_GRAY:
                brightness = 0x55;
                break;
            case Pallet::BLACK:
                brightness = 0x00;
                break;
            }
            auto index = pixel + (LY->getRegVal() * GAMEBOY_WIDTH);
            (*buffer)[index].red = brightness;
            (*buffer)[index].green = brightness;
            (*buffer)[index].blue = brightness;
        }

        if (LCDC->windowEnable()) {
            if (LY->getRegVal() >= WY->getRegVal()) {
                // TODO Render window
            }
        }
    }
    if (LCDC->objEnable()) {
        // TODO Render objects
    }
}

void PPU::moveScanLine() {
    LY->setRegVal((LY->getRegVal() + 1) % (GAMEBOY_HEIGHT + V_BLANK_CYCLES));
    if (LY->getRegVal() == LYC->getRegVal()) {
        // TODO Trigger correct interrupt
    }
}

std::shared_ptr<ReadWriteDevice> PPU::getVRam() const { return vRam; }

std::shared_ptr<ReadWriteDevice> PPU::getBgp() const { return BGP; }

std::shared_ptr<ReadWriteDevice> PPU::getObp0() const { return OBP0; }

std::shared_ptr<ReadWriteDevice> PPU::getObp1() const { return OBP1; }

std::shared_ptr<ReadWriteDevice> PPU::getLcdc() const { return LCDC; }

std::shared_ptr<ReadWriteDevice> PPU::getStat() const { return STAT; }

std::shared_ptr<ReadWriteDevice> PPU::getScy() const { return SCY; }

std::shared_ptr<ReadWriteDevice> PPU::getScx() const { return SCX; }

std::shared_ptr<ReadWriteDevice> PPU::getLy() const { return LY; }

std::shared_ptr<ReadWriteDevice> PPU::getLyc() const { return LYC; }

std::shared_ptr<ReadWriteDevice> PPU::getWy() const { return WY; }

std::shared_ptr<ReadWriteDevice> PPU::getWx() const { return WX; }

std::shared_ptr<ReadWriteDevice> PPU::getDma() const { return DMA; }
