#include "LCDCRegister.h"
#include "bitUtils.h"
const constexpr uint16_t TILE_MAP_0_START_ADDR{ 0x9800U };
const constexpr uint16_t TILE_MAP_1_START_ADDR{ 0x9C00U };

LCDCRegister::LCDCRegister(uint16_t addr)
  : BasicRegister(addr) {}

bool LCDCRegister::displayEnable() {
    const uint8_t BIT = 7;
    return readBit(getRegVal(), BIT);
}

uint16_t LCDCRegister::windowTileMap() {
    const uint8_t BIT = 6;
    return readBit(getRegVal(), BIT) ? TILE_MAP_1_START_ADDR : TILE_MAP_0_START_ADDR;
}

bool LCDCRegister::windowEnable() {
    const uint8_t BIT = 5;
    return readBit(getRegVal(), BIT);
}

uint16_t LCDCRegister::bgWindowTileData() {
    const uint8_t BIT = 4;
    return readBit(getRegVal(), BIT) ? TILE_DATA_SIGNED_START_ADDR : TILE_DATA_UNSIGNED_START_ADDR;
}

uint16_t LCDCRegister::bgTileMap() {
    const uint8_t BIT = 3;
    return readBit(getRegVal(), BIT) ? TILE_MAP_1_START_ADDR : TILE_MAP_0_START_ADDR;
}
uint8_t LCDCRegister::objSize() {
    const uint8_t BIT = 2;
    const uint8_t DOUBLE_SIZE = 16;
    const uint8_t SINGLE_SIZE = 8;
    return readBit(getRegVal(), BIT) ? DOUBLE_SIZE : SINGLE_SIZE;
}
bool LCDCRegister::objEnable() {
    const uint8_t BIT = 1;
    return readBit(getRegVal(), BIT);
}
bool LCDCRegister::bgDisplay() {
    const uint8_t BIT = 0;
    return readBit(getRegVal(), BIT);
}
