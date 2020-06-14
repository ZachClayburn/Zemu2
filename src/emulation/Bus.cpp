#include "Bus.h"

#include "RamBank.h"


Bus::Bus(std::shared_ptr<std::array<Pixel, PIXEL_COUNT>> screenBuffer, void (*screenCallback)())
  : ppu(std::move(screenBuffer), screenCallback),
    bootRom(std::make_shared<BootRom>()),
    wRam(std::make_shared<RamBank>(8 * 1024, 0xC000U)),
    hRam(std::make_shared<RamBank>(126, 0xFF80U)), cpu(this) {
    
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
