#include "GameBoy.h"

#include "BootRom.h"
#include "RamBank.h"

GameBoy::GameBoy()
  : bootRom(std::make_shared<BootRom>()),
    wRam(std::make_shared<RamBank>(8 * 1024, 0xC000U)),
    hRam(std::make_shared<RamBank>(126, 0xFF80U)) {
    
    int i = 0;
    devices.at(i++) = bootRom;
    devices.at(i++) = wRam;
    devices.at(i++) = IRamBank::getEcho(0xE000U, wRam);
    devices.at(i++) = hRam;
}
