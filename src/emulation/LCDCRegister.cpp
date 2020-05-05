#include "LCDCRegister.h"

LCDCRegister::LCDCRegister(uint16_t addr)
  : BasicRegister(addr) {}

bool LCDCRegister::displayEnable() {
    const uint8_t BIT = 7;
    return readBit(BIT);
}

uint16_t LCDCRegister::windowTileMap() {
    const uint8_t BIT = 6;
    //TODO Find out what these values are and name them
    return readBit(BIT) ? 0x9C00U : 0x9800U;
}

bool LCDCRegister::windowEnable() {
    const uint8_t BIT = 5;
    return readBit(BIT);
}

uint16_t LCDCRegister::bgWindowTileData() {
    const uint8_t BIT = 4;
    //TODO Find out what these values are and name them
    return readBit(BIT) ? 0x8000U : 0x8800U;
}

uint16_t LCDCRegister::bgTileMap() {
    const uint8_t BIT = 3;
    //TODO Find out what these values are and name them
    return readBit(BIT) ? 0x9C00U : 0x9800U;
}
uint8_t LCDCRegister::objSize() {
    const uint8_t BIT = 2;
    const uint8_t DOUBLE_SIZE = 16;
    const uint8_t SINGLE_SIZE = 8;
    return readBit(BIT) ? DOUBLE_SIZE : SINGLE_SIZE;
}
bool LCDCRegister::objEnable() {
    const uint8_t BIT = 1;
    return readBit(BIT);
}
bool LCDCRegister::bgDisplay() {
    const uint8_t BIT = 0;
    return readBit(BIT);
}
