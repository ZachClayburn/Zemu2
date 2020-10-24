#ifndef ZEMU2_INDIRECTLOADTOPARAMETERANDPLUSONE_H
#define ZEMU2_INDIRECTLOADTOPARAMETERANDPLUSONE_H

#include "Operation.h"

class IndirectLoadToParameterAndPlusOne : public Operation
{
  public:
    IndirectLoadToParameterAndPlusOne(IBus* busIn, CPURegisters* registersIn);
    ~IndirectLoadToParameterAndPlusOne() override = default;

    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static int LENGTH{ 18 };// TODO Verify
    IBus* bus;
    CPURegisters* registers;
};


#endif// ZEMU2_INDIRECTLOADTOPARAMETERANDPLUSONE_H
