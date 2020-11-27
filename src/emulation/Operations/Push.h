#ifndef ZEMU2_PUSH_H
#define ZEMU2_PUSH_H

#include "Operation.h"

class Push : public Operation
{
  public:
    enum Target{ BC, DE, HL, AF };
    Push(IBus* busIn, CPURegisters* registersIn, Target targetIn);
    ~Push() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static uint8_t LENGTH{ 16 };
    IBus* bus;
    CPURegisters* registers;
    Target target;
};


#endif// ZEMU2_PUSH_H
