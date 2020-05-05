#include "Pallet.h"
Pallet::Pallet(uint16_t addr)
  : palletAddr(addr),
    shades{ WHITE, WHITE, WHITE, WHITE } {}

uint8_t Pallet::read(uint16_t  /*addr*/) {
    uint8_t regValue{ 0x00U };
    for (unsigned int i = 0; i < 4; i++) {
        regValue |= static_cast<unsigned>(shades.at(i) << (2U * i));
    }
    return regValue;
}

void Pallet::write(uint16_t  /*addr*/, uint8_t val) {
    for (unsigned int i = 0; i < 4; i++) {
        shades.at(i) = static_cast<Shade>(((0b11U << 2 * i) & val) >> 2 * i);
    }
}

bool Pallet::accepts(uint16_t addr) {
    return addr == palletAddr;
}
Pallet::Shade Pallet::operator[](uint8_t n) {
    return shades.at(n);
}
