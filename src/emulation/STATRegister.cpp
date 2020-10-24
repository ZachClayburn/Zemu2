#include "STATRegister.h"
#include "bitUtils.h"

bool STATRegister::coincidenceInterruptEnabled() {
    const uint8_t BIT = 6;
    return readBit(getRegVal(), BIT);
}

bool STATRegister::oamInterruptEnabled() {
    const uint8_t BIT = 5;
    return readBit(getRegVal(), BIT);
}

bool STATRegister::vBlankInterruptEnabled() {
    const uint8_t BIT = 4;
    return readBit(getRegVal(), BIT);
}

bool STATRegister::hBlankInterruptEnabled() {
    const uint8_t BIT = 3;
    return readBit(getRegVal(), BIT);
}

bool STATRegister::coincidenceFlag() const { return coincidence; }

STATRegister::MODE STATRegister::modeFlag() { return mode; }

void STATRegister::setCoincidence(bool flag) { STATRegister::coincidence = flag; }

void STATRegister::setMode(STATRegister::MODE newMode) { STATRegister::mode = newMode; }
uint8_t STATRegister::read(uint16_t /*addr*/) {
    const uint8_t BIT_MASK = 0b11111000U;
    return (static_cast<uint8_t>(getRegVal() & BIT_MASK)) | (coincidence ? 0b100U : 0) | mode;
}
