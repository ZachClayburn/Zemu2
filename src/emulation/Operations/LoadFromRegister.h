#ifndef ZEMU2_LOADFROMREGISTER_H
#define ZEMU2_LOADFROMREGISTER_H

#include "Operation.h"

class LoadFromRegister : public Operation
{
  public:
    enum Targets : uint8_t {
        A,
        B,
        C,
        D,
        E,
        H,
        L,
    };
    LoadFromRegister(CPURegisters *registersIn, Targets targetIn);
    ~LoadFromRegister() override = default;
    
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static int LENGTH{ 2 };
    CPURegisters *registers;
    Targets target;
};


#endif//ZEMU2_LOADFROMREGISTER_H
