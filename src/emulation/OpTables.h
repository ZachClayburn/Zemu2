#ifndef ZEMU2_OPTABLES_H
#define ZEMU2_OPTABLES_H


#include <array>
#include <functional>
#include "Instruction.h"

class IBus;
class CPURegisters;


using OpcodeFun = std::function<Instruction(IBus* const, CPURegisters* const)>;

class OpTables
{
  public:
    OpTables();
    OpcodeFun operator[](uint8_t opcode);

  private:
    void addBasicLoad(uint8_t opcode, uint8_t target, const std::string& label);
    void addIndirectLoadFromRegisterPair(uint8_t opcode,
      uint8_t fromTarget,
      uint8_t toTarget,
      const std::string& label);
    void addIndirectLoadToRegisterPair(uint8_t opcode,
      uint8_t fromTarget,
      uint8_t toTarget,
      const std::string& label);
    void addRegisterToRegisterLoad(uint8_t opcode,
      uint8_t fromTarget,
      uint8_t toTarget,
      const std::string& label);

    const uint8_t PREFIX_ADDR{ 0xCBU };
    std::array<OpcodeFun, 256> opTable;
    std::array<OpcodeFun, 256> prefixTable;
};


#endif// ZEMU2_OPTABLES_H
