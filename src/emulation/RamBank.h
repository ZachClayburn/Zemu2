#ifndef ZEMU2_RAMBANK_H
#define ZEMU2_RAMBANK_H

#include <vector>
#include "IRamBank.h"

class RamBank : public IRamBank
{
  public:
    RamBank(uint16_t bankSize, uint16_t startAddr);
    
    uint8_t read(uint16_t addr) override;
    
    void write(uint16_t addr, uint8_t val) override;
    
  private:
    std::vector<uint8_t> memory;
};


#endif//ZEMU2_RAMBANK_H
