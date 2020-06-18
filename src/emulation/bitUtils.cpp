#include "bitUtils.h"

bool readBit(uint8_t byte, uint8_t bit){
    return static_cast<bool>(byte & (0b1U << bit));
}

[[nodiscard]] uint16_t mergeBytes(uint8_t  highByte, uint8_t  lowByte) {
    constexpr const unsigned int shift = 8U;
    return static_cast<unsigned>(highByte << shift) | lowByte;
}

void splitBytes(uint16_t merged, uint8_t &highByte, uint8_t &lowByte) {
    constexpr const uint8_t bitMask = 0xFFU;
    constexpr const unsigned int shift = 8U;
    lowByte = merged & bitMask;
    highByte = (merged >> shift);
}