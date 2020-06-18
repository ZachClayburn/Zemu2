#ifndef ZEMU2_INDIRECTLOADTOREGISTERPAIR_H
#define ZEMU2_INDIRECTLOADTOREGISTERPAIR_H

#include "Operation.h"

class IndirectLoadToRegisterPair : public Operation
{
  public:
    enum Targets : uint8_t {
        BC,
        DE,
        HL,
        HLi,
        HLd,
    };
    IndirectLoadToRegisterPair(IBus *busIn, CPURegisters *registersIn, IndirectLoadToRegisterPair::Targets targetIn);
    ~IndirectLoadToRegisterPair() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    const constexpr static int LENGTH{ 6 };

    IBus *bus;
    CPURegisters *registers;
    Targets target;
};


#endif//ZEMU2_INDIRECTLOADTOREGISTERPAIR_H
