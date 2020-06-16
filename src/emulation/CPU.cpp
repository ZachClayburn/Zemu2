#include "CPU.h"

#include "CPURegisters.h"
#include "Bus.h"
#include "Instruction.h"
#include "Operation.h"

CPU::CPU(IBus *owningBus)
  : registers(std::make_shared<CPURegisters>()),
    bus(owningBus) {}

void CPU::clock() {
    switch (state) {

    case RUNNING:
        if (instruction.isDone()){
            auto opcode = bus->read(registers->getPC());
            instruction = tables[opcode](bus, registers.get());
        } else {
            instruction.clock();
        }
        break;
    case HALTED:
        [[fallthrough]];
    case STOPPED:
        //These are effectively the same for now
        break;
    }
}
