#include "Bus.h"

#include "RamBank.h"


Bus::Bus(std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer, void (*screenCallback)())
  : ppu(std::move(screenBuffer), screenCallback), cpu(this), bootRom(std::make_shared<BootRom>()),
    wRam(std::make_shared<RamBank>(8 * 1024, 0xC000U)),
    hRam(std::make_shared<RamBank>(126, 0xFF80U)) {

    int i = 0;
    devices.at(i++) = bootRom;
    devices.at(i++) = wRam;
    devices.at(i++) = AbstractRamBank::getEcho(0xE000U, wRam);
    devices.at(i++) = hRam;
    devices.at(i++) = ppu.getVRam();
    devices.at(i++) = ppu.getBgp();
    devices.at(i++) = ppu.getObp0();
    devices.at(i++) = ppu.getObp1();
    devices.at(i++) = ppu.getLcdc();
    devices.at(i++) = ppu.getStat();
    devices.at(i++) = ppu.getScy();
    devices.at(i++) = ppu.getScx();
    devices.at(i++) = ppu.getLy();
    devices.at(i++) = ppu.getLyc();
    devices.at(i++) = ppu.getWy();
    devices.at(i++) = ppu.getWx();
    devices.at(i++) = ppu.getDma();
}
void Bus::clock() {
    cpu.clock();
    ppu.clock();
}

uint8_t Bus::read(uint16_t addr) {
    for (auto& device : devices) {
        if (device->accepts(addr)) { return device->read(addr); }
    }
    return 0xFFU;
}

void Bus::write(uint16_t addr, uint8_t val) {
    for (auto& device : devices) {
        if (device->accepts(addr)) {
            device->write(addr, val);
            break;
        }
    }
}
