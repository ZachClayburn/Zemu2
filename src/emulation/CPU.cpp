#include "CPU.h"

#include "CPURegisters.h"

CPU::CPU(Bus *owningBus)
  : registers(std::make_shared<CPURegisters>()),
    bus(owningBus) {}

void CPU::clock() {
}
