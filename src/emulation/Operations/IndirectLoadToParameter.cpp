#include "IndirectLoadToParameter.h"

#include "IBus.h"
#include "CPURegisters.h"
#include "bitUtils.h"

IndirectLoadToParameter::IndirectLoadToParameter(IBus* busIn, CPURegisters* registersIn)
  : Operation(LENGTH), bus(busIn), registers(registersIn) {}

interimValue_t IndirectLoadToParameter::operator()(interimValue_t value) {
    uint8_t highByte = bus->read(registers->getPC());
    registers->incPC();
    uint8_t lowByte = bus->read(registers->getPC());
    registers->incPC();
    auto addr = mergeBytes(highByte, lowByte);
    bus->write(addr, std::get<uint8_t>(value));
    return interimValue_t();
}
