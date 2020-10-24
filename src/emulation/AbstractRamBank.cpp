#include "AbstractRamBank.h"
#include "RamEcho.h"

AbstractRamBank::AbstractRamBank(uint16_t addrStart, uint16_t addrStop)
  : addrLow(addrStart), addrHigh(addrStop) {}

bool AbstractRamBank::accepts(uint16_t addr) { return (addr >= addrLow && addr <= addrHigh); }
uint16_t AbstractRamBank::getAddrStart() const { return addrLow; }
std::unique_ptr<AbstractRamBank> AbstractRamBank::getEcho(uint16_t startAddr,
  std::weak_ptr<AbstractRamBank> echoedBank) {
    auto bank = echoedBank.lock();
    uint16_t stopAddr = startAddr + bank->addrHigh - bank->addrLow;
    return std::make_unique<RamEcho>(startAddr, stopAddr, echoedBank);
}
