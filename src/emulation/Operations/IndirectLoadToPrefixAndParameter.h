#ifndef ZEMU2_INDIRECTLOADTOPREFIXANDPARAMETER_H
#define ZEMU2_INDIRECTLOADTOPREFIXANDPARAMETER_H

#include "Operation.h"

class IndirectLoadToPrefixAndParameter : public Operation
{
  public:
    IndirectLoadToPrefixAndParameter(IBus *busIn, CPURegisters *registersIn);
    ~IndirectLoadToPrefixAndParameter() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static int LENGTH{ 6 };
    constexpr const static uint16_t PREFIX{ 0xFF00U };
    IBus *bus;
    CPURegisters *registers;

};


#endif//ZEMU2_INDIRECTLOADTOPREFIXANDPARAMETER_H
