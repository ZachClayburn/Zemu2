#include "LoadFromRegister.h"

#include <stdexcept>
#include "CPURegisters.h"

LoadFromRegister::LoadFromRegister(CPURegisters* registersIn, Targets targetIn)
  : Operation(LENGTH), registers(registersIn), target(targetIn) {}

interimValue_t LoadFromRegister::operator()(interimValue_t /*value*/) {
    switch (target) {

    case A:
        return registers->getA();
    case B:
        return registers->getB();
    case C:
        return registers->getC();
    case D:
        return registers->getD();
    case E:
        return registers->getE();
    case H:
        return registers->getH();
    case L:
        return registers->getL();
    default:
        throw std::invalid_argument("Invalid target register passed to LoadFromRegister");
    }
}
