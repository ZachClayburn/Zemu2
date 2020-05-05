#ifndef ZEMU2_RAMECHO_H
#define ZEMU2_RAMECHO_H


#include "AbstractRamBank.h"

class RamEcho : public AbstractRamBank
{
  public:
    RamEcho(uint16_t startAddr, uint16_t stopAddr, std::weak_ptr<AbstractRamBank> echoedRam);
    uint8_t read(uint16_t addr) override;
    void write(uint16_t addr, uint8_t val) override;

  private:
    std::weak_ptr<AbstractRamBank> echoedBank;
};


#endif//ZEMU2_RAMECHO_H
