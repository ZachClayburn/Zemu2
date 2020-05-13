#ifndef ZEMU2_BITUTILS_H
#define ZEMU2_BITUTILS_H

#include <cstdint>

[[nodiscard]] bool readBit(uint8_t byte, uint8_t bit){
    return static_cast<bool>(byte & (0b1U << bit));
}

#endif//ZEMU2_BITUTILS_H
