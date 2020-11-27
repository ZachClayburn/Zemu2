#ifndef ZEMU2_POP_H
#define ZEMU2_POP_H

#include "Operation.h"

class Pop : public Operation
{
  public:
    enum Target { BC, DE, HL, AF };
    Pop(IBus* busIn, CPURegisters* registersIn, Target targetIn);
    ~Pop() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static uint8_t LENGTH{ 12 };
    IBus* bus;
    CPURegisters* registers;
    Target target;
};


#endif// ZEMU2_POP_H
