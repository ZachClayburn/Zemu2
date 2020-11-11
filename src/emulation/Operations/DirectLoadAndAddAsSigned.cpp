#include "DirectLoadAndAddAsSigned.h"

#include "Bus.h"
#include "CPURegisters.h"

DirectLoadAndAddAsSigned::DirectLoadAndAddAsSigned(IBus* busIn, CPURegisters* registersIn)
  : Operation(LENGTH), bus(busIn), registers(registersIn) {}

interimValue_t DirectLoadAndAddAsSigned::operator()(interimValue_t value) {
    auto parameter = static_cast<int8_t>(bus->read(registers->getPC()));
    registers->incPC();

    if (std::holds_alternative<uint8_t>(value)) {
        return static_cast<uint8_t>(std::get<uint8_t>(value) + parameter);
    }
    return static_cast<uint16_t>(std::get<uint16_t>(value) + parameter);
}
