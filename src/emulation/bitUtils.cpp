#include "bitUtils.h"

#include <limits>

bool readBit(uint8_t byte, uint8_t bit) { return static_cast<bool>(byte & (0b1U << bit)); }

uint8_t setBit(uint8_t byte, uint8_t bit, bool value) {
    return value ? (byte | (1U << bit)) : (byte & ~(1U << bit));
}
bool testCarry(uint8_t byte1, uint8_t byte2) {
    return (static_cast<uint16_t>(byte1) + static_cast<uint16_t>(byte2)
            > std::numeric_limits<uint8_t>::max());
}

bool testHalfCarry(uint8_t byte1, uint8_t byte2) {
    return (((byte1 & 0xFU) + (byte2 & 0xFU)) & 0x10U) == 0x10U;
}

[[nodiscard]] uint16_t mergeBytes(uint8_t highByte, uint8_t lowByte) {
    constexpr const unsigned int shift = 8U;
    return static_cast<unsigned>(highByte << shift) | lowByte;
}

void splitBytes(uint16_t merged, uint8_t& highByte, uint8_t& lowByte) {
    constexpr const uint8_t bitMask = 0xFFU;
    constexpr const unsigned int shift = 8U;
    lowByte = merged & bitMask;
    highByte = (merged >> shift);
}
std::tuple<uint8_t, uint8_t> splitBytes(uint16_t value) {
    constexpr const uint8_t bitMask = 0xFFU;
    constexpr const unsigned int shift = 8U;

    const uint8_t highByte = value >> shift;
    const uint8_t lowByte = value & bitMask;
    return { highByte, lowByte };
}
