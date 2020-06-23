#ifndef ZEMU2_LOADTOREGISTERPAIR_H
#define ZEMU2_LOADTOREGISTERPAIR_H

#include "Operation.h"

class LoadToRegisterPair : public Operation
{
  public:
    enum Targets {
        BC,
        DE,
        HL,
        SP
    };
    LoadToRegisterPair(CPURegisters *registersIn, Targets targetIn);
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static uint8_t LENGTH{ 6 };
    CPURegisters *registers;
    Targets target;
};


#endif//ZEMU2_LOADTOREGISTERPAIR_H
