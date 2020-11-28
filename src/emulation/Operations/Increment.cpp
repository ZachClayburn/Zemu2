#include "Increment.h"

#include "CPURegisters.h"

const constexpr static uint8_t HALF_CARY_VALUE{ 0x0F };

Increment::Increment(CPURegisters* registersIn, Target targetIn)
  : Operation(LENGTH), target(targetIn), registers(registersIn) {}

interimValue_t Increment::operator()(interimValue_t value) {
    uint8_t oldVal = 0;
    switch (target) {
    case A:
        oldVal = registers->getA();
        break;
    case B:
        oldVal = registers->getB();
        break;
    case C:
        oldVal = registers->getC();
        break;
    case D:
        oldVal = registers->getD();
        break;
    case E:
        oldVal = registers->getE();
        break;
    case H:
        oldVal = registers->getH();
        break;
    case L:
        oldVal = registers->getL();
        break;
    }
    const uint8_t newVal = oldVal + 1;
    switch (target) {
    case A:
        registers->setA(newVal);
        break;
    case B:
        registers->setB(newVal);
        break;
    case C:
        registers->setC(newVal);
        break;
    case D:
        registers->setD(newVal);
        break;
    case E:
        registers->setE(newVal);
        break;
    case H:
        registers->setH(newVal);
        break;
    case L:
        registers->setL(newVal);
        break;
    }

    registers->setNFlag(false);
    registers->setZFlag(newVal == 0);
    registers->setHFlag(oldVal == HALF_CARY_VALUE);
    return value;
}
