#include "IndirectLoadToPrefixAndCRegister.h"

#include "IBus.h"
#include "CPURegisters.h"

IndirectLoadToPrefixAndCRegister::IndirectLoadToPrefixAndCRegister(IBus *busIn, CPURegisters *registersIn) : Operation(LENGTH), bus(busIn), registers(registersIn) {}

interimValue_t IndirectLoadToPrefixAndCRegister::operator()(interimValue_t value) {
    uint16_t addr = PREFIX + registers->getC();
    bus->write(addr, std::get<uint8_t>(value));
    return interimValue_t();
}
