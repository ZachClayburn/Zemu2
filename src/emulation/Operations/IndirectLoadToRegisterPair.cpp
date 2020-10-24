#include "IndirectLoadToRegisterPair.h"

#include "IBus.h"
#include "CPURegisters.h"
IndirectLoadToRegisterPair::IndirectLoadToRegisterPair(IBus* busIn,
  CPURegisters* registersIn,
  IndirectLoadToRegisterPair::Targets targetIn)
  : Operation(LENGTH), bus(busIn), registers(registersIn), target(targetIn) {}

interimValue_t IndirectLoadToRegisterPair::operator()(interimValue_t value) {
    uint16_t addr{ 0 };

    switch (target) {
    case BC:
        addr = registers->getBC();
        break;
    case DE:
        addr = registers->getDE();
        break;
    case HL:
        [[fallthrough]];
    case HLi:
        [[fallthrough]];
    case HLd:
        addr = registers->getHL();
        break;
    }

    bus->write(addr, std::get<uint8_t>(value));

    if (target == HLi) {
        registers->indHL();
    } else if (target == HLd) {
        registers->decHL();
    }

    return std::monostate();
}
