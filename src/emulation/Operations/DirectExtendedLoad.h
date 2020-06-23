#ifndef ZEMU2_DIRECTEXTENDEDLOAD_H
#define ZEMU2_DIRECTEXTENDEDLOAD_H

#include "Operation.h"

class DirectExtendedLoad : public Operation
{
  public:
    DirectExtendedLoad(IBus *busIn, CPURegisters *registersIn);

    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static uint8_t LENGTH{ 6 };
    IBus *bus;
    CPURegisters *registers;
};


#endif//ZEMU2_DIRECTEXTENDEDLOAD_H
