#ifndef ZEMU2_INDIRECTLOADFROMPREFIXANDCREGISTER_H
#define ZEMU2_INDIRECTLOADFROMPREFIXANDCREGISTER_H

#include "Operation.h"

class IndirectLoadFromPrefixAndCRegister : public Operation
{
  public:
    IndirectLoadFromPrefixAndCRegister(IBus* busIn, CPURegisters* registersIn);
    ~IndirectLoadFromPrefixAndCRegister() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static int LENGTH{ 6 };
    constexpr const static uint16_t PREFIX{ 0xFF00U };
    IBus* bus;
    CPURegisters* registers;
};


#endif// ZEMU2_INDIRECTLOADFROMPREFIXANDCREGISTER_H
