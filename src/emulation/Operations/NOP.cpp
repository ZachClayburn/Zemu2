#include "NOP.h"
NOP::NOP() : Operation(LENGTH) {}

interimValue_t NOP::operator()(interimValue_t value) { return value; }
