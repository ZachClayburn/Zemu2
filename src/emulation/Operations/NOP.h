#ifndef ZEMU2_NOP_H
#define ZEMU2_NOP_H

#include "Operation.h"

class NOP : public Operation
{
  public:
    explicit NOP();
    ~NOP() override = default;
    interimValue_t operator()(interimValue_t value) override;

  private:
    constexpr const static uint8_t LENGTH = 4;
};


#endif// ZEMU2_NOP_H
