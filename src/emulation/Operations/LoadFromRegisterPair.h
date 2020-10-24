#ifndef ZEMU2_LOADFROMREGISTERPAIR_H
#define ZEMU2_LOADFROMREGISTERPAIR_H

#include "Operation.h"

class LoadFromRegisterPair : public Operation
{
  public:
    enum Targets : uint8_t {
        BC,
        DE,
        HL,
        AF,
        SP,
        PC,
    };
    LoadFromRegisterPair(CPURegisters* registersIn, Targets targetIn);
    ~LoadFromRegisterPair() override = default;

    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static int LENGTH{ 2 };// TODO verify
    CPURegisters* registers;
    Targets target;
};


#endif// ZEMU2_LOADFROMREGISTERPAIR_H
