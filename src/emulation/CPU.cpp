#include "CPU.h"

#include "CPURegisters.h"
#include "Bus.h"

CPU::CPU(IBus *owningBus)
  : registers(std::make_shared<CPURegisters>()),
    bus(owningBus),
    instruction{0x00U, "", {}} {}

void CPU::clock() {
    switch (state) {

    case RUNNING:
        if (instruction.isDone()) {
            auto opcode = bus->read(registers->getPC());
            instruction = tables[opcode](bus, registers.get());
            registers->incPC();
        }
        instruction.clock();
        break;
    case HALTED:
        [[fallthrough]];
    case STOPPED:
        //These are effectively the same for now
        break;
    }
}
std::shared_ptr<CPURegisters> CPU::getRegisters() {
    return registers;
}
