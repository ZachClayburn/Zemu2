#ifndef ZEMU2_LOADTOREGISTER_H
#define ZEMU2_LOADTOREGISTER_H

#include "Operation.h"

class LoadToRegister : public Operation
{
  public:
    enum RegisterTarget : uint8_t {
        A,
        B,
        C,
        D,
        E,
        H,
        L,
    };
    
    LoadToRegister(CPURegisters* registersIn, RegisterTarget targetIn);
    ~LoadToRegister() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static uint8_t LENGTH{ 2 };
    CPURegisters *registers;
    RegisterTarget target;
};


#endif//ZEMU2_LOADTOREGISTER_H
