#include "GameBoy.h"

#include "BootRom.h"


GameBoy::GameBoy()
  : bootRom(std::make_shared<BootRom>()) {
    devices[0] = bootRom;
}
