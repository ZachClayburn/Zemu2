#include "IndirectLoadFromPrefixAndCRegister.h"

#include "CPURegisters.h"
#include "IBus.h"

IndirectLoadFromPrefixAndCRegister::IndirectLoadFromPrefixAndCRegister(IBus *busIn, CPURegisters *registersIn) : Operation(LENGTH), bus(busIn), registers(registersIn) {}

interimValue_t IndirectLoadFromPrefixAndCRegister::operator()(interimValue_t /*value*/) {
    uint16_t addr = PREFIX + registers->getC();
    return bus->read(addr);
}
