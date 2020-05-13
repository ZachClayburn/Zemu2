#include "BasicRegister.h"
BasicRegister::BasicRegister(uint16_t addr)
  : regAddr(addr) {}

uint8_t BasicRegister::read(uint16_t  /*addr*/) {
    return regVal;
}

void BasicRegister::write(uint16_t  /*addr*/, uint8_t val) {
    regVal = val;
}

bool BasicRegister::accepts(uint16_t addr) {
    return addr == regAddr;
}

uint8_t BasicRegister::getRegVal() const {
    return regVal;
}
