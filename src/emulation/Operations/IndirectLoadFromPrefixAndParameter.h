#ifndef ZEMU2_INDIRECTLOADFROMPREFIXANDPARAMETER_H
#define ZEMU2_INDIRECTLOADFROMPREFIXANDPARAMETER_H

#include "Operation.h"

class IndirectLoadFromPrefixAndParameter : public Operation
{
  public:
    IndirectLoadFromPrefixAndParameter(IBus *busIn, CPURegisters *registersIn);
    ~IndirectLoadFromPrefixAndParameter() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static int LENGTH{ 6 };
    constexpr const static uint16_t PREFIX{ 0xFF00U };
    IBus *bus;
    CPURegisters *registers;
};


#endif//ZEMU2_INDIRECTLOADFROMPREFIXANDPARAMETER_H
