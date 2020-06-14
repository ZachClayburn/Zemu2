#include "bitUtils.h"

bool readBit(uint8_t byte, uint8_t bit){
    return static_cast<bool>(byte & (0b1U << bit));
}

[[nodiscard]] uint16_t mergeBytes(uint8_t  /*highByte*/, uint8_t  /*lowByte*/) {
    return 0;//TODO Implement this
}

void splitBytes(uint16_t /*merged*/, uint8_t &/*highByte*/, uint8_t &/*lowByte*/) {
    //TODO Implement this
}