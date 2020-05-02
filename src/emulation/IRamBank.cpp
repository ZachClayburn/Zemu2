#include "IRamBank.h"
#include "RamEcho.h"

IRamBank::IRamBank(uint16_t addrStart, uint16_t addrStop)
  : addrLow(addrStart), addrHigh(addrStop) {}

bool IRamBank::accepts(uint16_t addr) {
    return (addr >= addrLow && addr <= addrHigh);
}
uint16_t IRamBank::getAddrStart() const {
    return addrLow;
}
std::unique_ptr<IRamBank> IRamBank::getEcho(uint16_t startAddr, std::weak_ptr<IRamBank> echoedBank) {
    auto bank = echoedBank.lock();
    uint16_t stopAddr = startAddr + bank->addrHigh - bank->addrLow;
    return std::make_unique<RamEcho>(startAddr, stopAddr, echoedBank);
}
