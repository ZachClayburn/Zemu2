#ifndef ZEMU2_BITUTILS_H
#define ZEMU2_BITUTILS_H

#include <cstdint>
#include <tuple>

[[nodiscard]] bool readBit(uint8_t byte, uint8_t bit);

[[nodiscard]] uint16_t mergeBytes(uint8_t highByte, uint8_t lowByte);

// TODO Deprecate this
// [[deprecated("Use std::tuple<uint8_t, uint8_t> splitBytes(uint16_t value)")]]
void splitBytes(uint16_t merged, uint8_t& highByte, uint8_t& lowByte);

[[nodiscard]] std::tuple<uint8_t, uint8_t> splitBytes(uint16_t value);

#endif// ZEMU2_BITUTILS_H
