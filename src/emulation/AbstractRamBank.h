#ifndef ZEMU2_ABSTRACTRAMBANK_H
#define ZEMU2_ABSTRACTRAMBANK_H

#include <memory>
#include "ReadWriteDevice.h"

class AbstractRamBank : public ReadWriteDevice
{
  public:
    AbstractRamBank(uint16_t addrStart, uint16_t addrStop);
    
    bool accepts(uint16_t addr) override;
    
    static std::unique_ptr<AbstractRamBank> getEcho(uint16_t startAddr, std::weak_ptr<AbstractRamBank> echoedBank);
    
    [[nodiscard]] uint16_t getAddrStart() const;
    
  private:
    uint16_t addrLow;
    uint16_t addrHigh;
};


#endif//ZEMU2_ABSTRACTRAMBANK_H
