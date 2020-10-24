#include "LoadToRegister.h"

#include "CPURegisters.h"

LoadToRegister::LoadToRegister(CPURegisters* registersIn, LoadToRegister::Targets targetIn)
  : Operation(LENGTH), registers(registersIn), target(targetIn) {}

interimValue_t LoadToRegister::operator()(interimValue_t value) {
    switch (target) {

    case A:
        registers->setA(std::get<uint8_t>(value));
        break;
    case B:
        registers->setB(std::get<uint8_t>(value));
        break;
    case C:
        registers->setC(std::get<uint8_t>(value));
        break;
    case D:
        registers->setD(std::get<uint8_t>(value));
        break;
    case E:
        registers->setE(std::get<uint8_t>(value));
        break;
    case H:
        registers->setH(std::get<uint8_t>(value));
        break;
    case L:
        registers->setL(std::get<uint8_t>(value));
        break;
    }
    return interimValue_t();
}
