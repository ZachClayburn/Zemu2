#include "IndirectLoadFromParameter.h"

#include "IBus.h"
#include "CPURegisters.h"
#include "bitUtils.h"

IndirectLoadFromParameter::IndirectLoadFromParameter(IBus *busIn, CPURegisters *registersIn) : Operation(LENGTH), bus(busIn), registers(registersIn) {}

interimValue_t IndirectLoadFromParameter::operator()(interimValue_t /*value*/) {
    uint8_t highByte = bus->read(registers->getPC());
    registers->incPC();
    uint8_t lowByte = bus->read(registers->getPC());
    registers->incPC();
    auto addr = mergeBytes(highByte, lowByte);
    return bus->read(addr);
}
