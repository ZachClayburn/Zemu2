#ifndef ZEMU2_INDIRECTLOADFROMPARAMETER_H
#define ZEMU2_INDIRECTLOADFROMPARAMETER_H

#include "Operation.h"

class IndirectLoadFromParameter : public Operation
{
  public:
    IndirectLoadFromParameter(IBus *busIn, CPURegisters *registersIn);
    ~IndirectLoadFromParameter() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static int LENGTH{ 14 };
    IBus *bus;
    CPURegisters *registers;
};


#endif//ZEMU2_INDIRECTLOADFROMPARAMETER_H
