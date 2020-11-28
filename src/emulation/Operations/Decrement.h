#ifndef ZEMU2_DECREMENT_H
#define ZEMU2_DECREMENT_H


#include "Operation.h"

class Decrement : public Operation
{
  public:
    enum Target{A, B, C, D, E, H, L};
    Decrement(CPURegisters* registersIn, Target targetIn);
    ~Decrement() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    const static constexpr uint8_t LENGTH{ 4 };
    Target target;
    CPURegisters* registers;
};


#endif// ZEMU2_DECREMENT_H
