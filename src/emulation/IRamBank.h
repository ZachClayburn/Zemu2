#ifndef ZEMU2_IRAMBANK_H
#define ZEMU2_IRAMBANK_H

#include <memory>
#include "ReadWriteDevice.h"

class IRamBank : public ReadWriteDevice
{
  public:
    IRamBank(uint16_t addrStart, uint16_t addrStop);
    
    bool accepts(uint16_t addr) override;
    
    static std::unique_ptr<IRamBank> getEcho(uint16_t startAddr, std::weak_ptr<IRamBank> echoedBank);
    
    [[nodiscard]] uint16_t getAddrStart() const;
    
  private:
    uint16_t addrLow;
    uint16_t addrHigh;
};


#endif//ZEMU2_IRAMBANK_H
