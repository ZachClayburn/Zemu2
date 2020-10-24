#include "IndirectLoadFromRegisterPair.h"

#include "CPURegisters.h"
#include "IBus.h"

IndirectLoadFromRegisterPair::IndirectLoadFromRegisterPair(IBus* busIn,
  CPURegisters* registersIn,
  Targets targetIn)
  : Operation(LENGTH), bus(busIn), registers(registersIn), target(targetIn) {}

interimValue_t IndirectLoadFromRegisterPair::operator()(interimValue_t value) {
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
    if (target == HLi) {
        registers->indHL();
    } else if (target == HLd) {
        registers->decHL();
    }

    value = bus->read(addr);
    return value;
}
