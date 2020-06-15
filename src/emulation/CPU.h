#ifndef ZEMU2_CPU_H
#define ZEMU2_CPU_H

#include <memory>
#include <array>
#include "OpTables.h"

class CPURegisters;
class Bus;

class CPU
{
  public:
    explicit CPU(Bus *owningBus);
    void clock();
    
  private:
    enum {
        RUNNING,
        HALTED,
        STOPPED,
    } state = RUNNING;

    std::shared_ptr<CPURegisters> registers;
    Bus *bus;
    OpTables tables;
    Instruction instruction;
    
};


#endif//ZEMU2_CPU_H
