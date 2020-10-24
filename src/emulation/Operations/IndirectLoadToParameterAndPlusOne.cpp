#include "IndirectLoadToParameterAndPlusOne.h"

#include "IBus.h"
#include "CPURegisters.h"
#include "bitUtils.h"

IndirectLoadToParameterAndPlusOne::IndirectLoadToParameterAndPlusOne(IBus *busIn, CPURegisters *registersIn)
  : Operation(LENGTH), bus(busIn), registers(registersIn) {}

interimValue_t IndirectLoadToParameterAndPlusOne::operator()(interimValue_t value) {
    const uint8_t highAddrByte = bus->read(registers->getPC());
    registers->incPC();
    const uint8_t lowAddrByte = bus->read(registers->getPC());
    registers->incPC();
    const auto addr = mergeBytes(highAddrByte, lowAddrByte);
    const auto fullValue = std::get<uint16_t>(value);
    const auto[highByte, lowByte] = splitBytes(fullValue);

    bus->write(addr, lowByte);
    bus->write(addr + 1, highByte);
    return interimValue_t();
}
