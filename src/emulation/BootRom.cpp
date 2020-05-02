#include "BootRom.h"

uint8_t BootRom::read(uint16_t addr) {
    if (addr == BOOT_REG_ADDR) {
        return ReadWriteDevice::BAD_READ;
    } else {
        return bootRom.at(addr);
    }
}

void BootRom::write(uint16_t addr, uint8_t val) {
    if (addr == BOOT_REG_ADDR and val == BOOT_REG_SHUTDOWN){
        enabled = false;
    }
}

bool BootRom::accepts(uint16_t addr) {
    return enabled && ((addr >= LOWER_BOUND && addr <= UPPER_BOUND) || addr == BOOT_REG_ADDR);
}

bool BootRom::bootComplete() {
    return false;
}
