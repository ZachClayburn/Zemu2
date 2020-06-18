#ifndef ZEMU2_INDIRECTLOADFROMREGISTERPAIR_H
#define ZEMU2_INDIRECTLOADFROMREGISTERPAIR_H

#include "Operation.h"

class IndirectLoadFromRegisterPair : public Operation
{
  public:
    enum Targets : uint8_t {
        BC,
        DE,
        HL,
        HLi,
        HLd,
    };
    IndirectLoadFromRegisterPair(IBus *busIn, CPURegisters *registersIn, Targets targetIn);
    ~IndirectLoadFromRegisterPair() override = default;
    
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static int LENGTH{6};
    IBus *bus;
    CPURegisters *registers;
    Targets target;
};


#endif//ZEMU2_INDIRECTLOADFROMREGISTERPAIR_H
