#include "LoadToRegisterPair.h"

#include "IBus.h"
#include "CPURegisters.h"

LoadToRegisterPair::LoadToRegisterPair(CPURegisters *registersIn, Targets targetIn)
  : Operation(LENGTH), registers(registersIn), target(targetIn) {}

interimValue_t LoadToRegisterPair::operator()(interimValue_t value) {
    switch (target) {
    case BC:
        registers->setBC(std::get<uint16_t>(value));
        break;
    case DE:
        registers->setDE(std::get<uint16_t>(value));
        break;
    case HL:
        registers->setHL(std::get<uint16_t>(value));
        break;
    case SP:
        registers->setSP(std::get<uint16_t>(value));
        break;
    }
    return interimValue_t();
}
