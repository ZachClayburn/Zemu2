#include "DirectLoad.h"

#include "Bus.h"
#include "CPURegisters.h"

DirectLoad::DirectLoad(IBus *busIn, CPURegisters *registersIn)
  : Operation(LENGTH), bus(busIn), registers(registersIn) {}

interimValue_t DirectLoad::operator()(interimValue_t /*value*/) {
    auto value = bus->read(registers->getPC());
    registers->incPC();
    return value;
}
