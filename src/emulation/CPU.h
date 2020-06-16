#ifndef ZEMU2_CPU_H
#define ZEMU2_CPU_H

#include <memory>
#include <array>
#include "OpTables.h"

class CPURegisters;
class IBus;

class CPU
{
  public:
    explicit CPU(IBus *owningBus);
    void clock();
    [[nodiscard]] std::shared_ptr<CPURegisters> getRegisters();

  private:
    enum {
        RUNNING,
        HALTED,
        STOPPED,
    } state = RUNNING;

    std::shared_ptr<CPURegisters> registers;
    IBus *bus;
    OpTables tables;
    Instruction instruction;
};


#endif//ZEMU2_CPU_H
