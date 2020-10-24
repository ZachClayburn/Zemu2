#include "RamBank.h"


RamBank::RamBank(uint16_t bankSize, uint16_t startAddr)
  : AbstractRamBank(startAddr, startAddr + bankSize), memory(bankSize) {
    // TODO Random initialize RAM on create
}

uint8_t RamBank::read(uint16_t addr) { return memory[addr - getAddrStart()]; }

void RamBank::write(uint16_t addr, uint8_t val) { memory[addr - getAddrStart()] = val; }
