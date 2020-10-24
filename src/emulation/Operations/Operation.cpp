#include "Operation.h"
Operation::Operation(uint8_t lengthIn) : length(lengthIn) {}

uint8_t Operation::getLength() const { return length; }
