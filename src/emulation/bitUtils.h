#ifndef ZEMU2_BITUTILS_H
#define ZEMU2_BITUTILS_H

#include <cstdint>

[[nodiscard]] bool readBit(uint8_t byte, uint8_t bit);

[[nodiscard]] uint16_t mergeBytes(uint8_t highByte, uint8_t lowByte);

void splitBytes(uint16_t merged, uint8_t &highByte, uint8_t &lowByte);

#endif//ZEMU2_BITUTILS_H
