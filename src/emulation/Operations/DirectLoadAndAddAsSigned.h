
#ifndef ZEMU2_DIRECTLOADANDADDASSIGNED_H
#define ZEMU2_DIRECTLOADANDADDASSIGNED_H

#include "Operation.h"

class DirectLoadAndAddAsSigned : public Operation
{
  public:
    DirectLoadAndAddAsSigned(IBus* busIn, CPURegisters* registersIn);
    ~DirectLoadAndAddAsSigned() override = default;

    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static uint8_t LENGTH{ 4 };
    IBus* bus;
    CPURegisters* registers;
};


#endif// ZEMU2_DIRECTLOADANDADDASSIGNED_H
