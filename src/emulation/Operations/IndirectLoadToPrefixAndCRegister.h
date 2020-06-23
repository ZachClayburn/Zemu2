#ifndef ZEMU2_INDIRECTLOADTOPREFIXANDCREGISTER_H
#define ZEMU2_INDIRECTLOADTOPREFIXANDCREGISTER_H

#include "Operation.h"

class IndirectLoadToPrefixAndCRegister : public Operation
{
  public:
    IndirectLoadToPrefixAndCRegister(IBus *busIn, CPURegisters *registersIn);
    ~IndirectLoadToPrefixAndCRegister() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static int LENGTH{ 6 };
    constexpr const static uint16_t PREFIX{ 0xFF00U };
    IBus *bus;
    CPURegisters *registers;
};


#endif//ZEMU2_INDIRECTLOADTOPREFIXANDCREGISTER_H
