#ifndef ZEMU2_CPU_H
#define ZEMU2_CPU_H

#include <memory>
#include <array>

#include "Instruction.h"

class CPURegisters;
class Bus;

class CPU
{
  public:
    explicit CPU(Bus *owningBus);
    void clock();

  private:
    std::shared_ptr<CPURegisters> registers;
    Bus* bus;
};


#endif//ZEMU2_CPU_H
