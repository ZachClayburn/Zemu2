#include "IndirectLoadToPrefixAndParameter.h"

#include "IBus.h"
#include "CPURegisters.h"

IndirectLoadToPrefixAndParameter::IndirectLoadToPrefixAndParameter(IBus *busIn, CPURegisters *registersIn) : Operation(LENGTH), bus(busIn), registers(registersIn) {}

interimValue_t IndirectLoadToPrefixAndParameter::operator()(interimValue_t value) {
    uint16_t addr = PREFIX + bus->read(registers->getPC());
    registers->incPC();

    bus->write(addr, std::get<uint8_t>(value));
    return interimValue_t();
}
