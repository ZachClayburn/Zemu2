#include "DirectExtendedLoad.h"

#include "Bus.h"
#include "CPURegisters.h"
#include "bitUtils.h"

DirectExtendedLoad::DirectExtendedLoad(IBus* busIn, CPURegisters* registersIn)
  : Operation(LENGTH), bus(busIn), registers(registersIn) {}

interimValue_t DirectExtendedLoad::operator()(interimValue_t /*value*/) {
    auto highBytes = bus->read(registers->getPC());
    registers->incPC();
    auto lowBytes = bus->read(registers->getPC());
    registers->incPC();

    return mergeBytes(highBytes, lowBytes);
}
