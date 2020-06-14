#include "Operation.h"
Operation::Operation(uint8_t length) : length(length) {}

uint8_t Operation::getLength() const {
    return length;
}
