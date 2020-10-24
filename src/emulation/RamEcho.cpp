#include "RamEcho.h"

#include <utility>
#include <stdexcept>

RamEcho::RamEcho(uint16_t startAddr, uint16_t stopAddr, std::weak_ptr<AbstractRamBank> echoedRam)
  : AbstractRamBank(startAddr, stopAddr), echoedBank(std::move(echoedRam)) {}

uint8_t RamEcho::read(uint16_t addr) {
    if (auto ram = echoedBank.lock()) {
        uint16_t echoAddr = ram->getAddrStart() + (addr - getAddrStart());
        return ram->read(echoAddr);
    }
    throw std::runtime_error("Echo of deleted ram bank read");
}
void RamEcho::write(uint16_t addr, uint8_t val) {
    if (auto ram = echoedBank.lock()) {
        uint16_t echoAddr = ram->getAddrStart() + (addr - getAddrStart());
        ram->write(echoAddr, val);
    }
    throw std::runtime_error("Echo of deleted ram bank written to");
}
