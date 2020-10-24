#include "LoadFromRegisterPair.h"

#include <stdexcept>
#include "CPURegisters.h"


LoadFromRegisterPair::LoadFromRegisterPair(CPURegisters* registersIn,
  LoadFromRegisterPair::Targets targetIn)
  : Operation(LENGTH), registers(registersIn), target(targetIn) {}


interimValue_t LoadFromRegisterPair::operator()(interimValue_t /*value*/) {
    switch (target) {

    case BC:
        return registers->getBC();
    case DE:
        return registers->getDE();
    case HL:
        return registers->getHL();
    case AF:
        return registers->getA();
    case SP:
        return registers->getSP();
    case PC:
        return registers->getPC();
    default:
        throw std::invalid_argument("Invalid register pair passed to LoadFromRegisterPair");
    }
}
