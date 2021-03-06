#ifndef ZEMU2_BASICREGISTER_H
#define ZEMU2_BASICREGISTER_H


#include "ReadWriteDevice.h"

class BasicRegister : public ReadWriteDevice
{
  public:
    explicit BasicRegister(uint16_t addr);
    uint8_t read(uint16_t addr) override;
    void write(uint16_t addr, uint8_t val) override;
    bool accepts(uint16_t addr) override;
    [[nodiscard]] uint8_t getRegVal() const;
    void setRegVal(uint8_t val);

  private:
    uint16_t regAddr;
    uint8_t regVal{ 0x00U };
};


#endif// ZEMU2_BASICREGISTER_H
