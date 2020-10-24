#include "IndirectLoadFromPrefixAndParameter.h"

#include "IBus.h"
#include "CPURegisters.h"

IndirectLoadFromPrefixAndParameter::IndirectLoadFromPrefixAndParameter(IBus* busIn,
  CPURegisters* registersIn)
  : Operation(LENGTH), bus(busIn), registers(registersIn) {}

interimValue_t IndirectLoadFromPrefixAndParameter::operator()(interimValue_t /*value*/) {
    uint16_t addr = PREFIX + bus->read(registers->getPC());
    registers->incPC();

    return bus->read(addr);
}
