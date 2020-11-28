#ifndef ZEMU2_INCREMENT_H
#define ZEMU2_INCREMENT_H

#include "Operation.h"

class Increment : public Operation
{
  public:
    enum Target { A, B, C, D, E, H, L };
    Increment(CPURegisters* registersIn, Target targetIn);
    ~Increment() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    const static constexpr uint8_t LENGTH{ 4 };
    Target target;
    CPURegisters* registers;
};


#endif// ZEMU2_INCREMENT_H
