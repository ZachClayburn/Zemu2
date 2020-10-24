#ifndef ZEMU2_INDIRECTLOADTOPARAMETER_H
#define ZEMU2_INDIRECTLOADTOPARAMETER_H

#include "Operation.h"

class IndirectLoadToParameter : public Operation
{
  public:
    IndirectLoadToParameter(IBus* busIn, CPURegisters* registersIn);
    ~IndirectLoadToParameter() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static int LENGTH{ 14 };
    IBus* bus;
    CPURegisters* registers;
};


#endif// ZEMU2_INDIRECTLOADTOPARAMETER_H
