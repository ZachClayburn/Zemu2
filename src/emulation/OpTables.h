#ifndef ZEMU2_OPTABLES_H
#define ZEMU2_OPTABLES_H


#include <array>
#include <functional>
#include <memory>
#include "Instruction.h"

class Bus;
class CPURegisters;

using OpcodeFun = std::function<Instruction(Bus *const, CPURegisters *const)>;

class OpTables
{
  public:
    OpTables();
    OpcodeFun lookupOpcode(uint8_t opcode);

  private:
    const uint8_t PREFIX_ADDR{ 0xFFU };//TODO Set this correctly
    std::array<OpcodeFun , 256> opTable;
    std::array<OpcodeFun , 256> prefixTable;
};


#endif//ZEMU2_OPTABLES_H
