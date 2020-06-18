#ifndef ZEMU2_DIRECTLOAD_H
#define ZEMU2_DIRECTLOAD_H

#include "Operation.h"

class DirectLoad : public Operation
{
  public:
    DirectLoad(IBus *busIn, CPURegisters *registersIn);
    ~DirectLoad() override = default;

    interimValue_t operator()(interimValue_t value) override;

  private:
    IBus *bus;
    CPURegisters *registers;

    constexpr const static uint8_t LENGTH{ 6 };
};


#endif//ZEMU2_DIRECTLOAD_H
