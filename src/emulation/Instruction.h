#ifndef ZEMU2_INSTRUCTION_H
#define ZEMU2_INSTRUCTION_H

#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <variant>

#include "Operations/Operation.h"

using InstructionList = std::vector<Operation*>;

class Instruction
{
  public:
    Instruction();
    Instruction(uint8_t opcodeIn, std::string labelIn, InstructionList opsIn);

    Instruction(const Instruction& old) = delete;
    Instruction(Instruction&& old) noexcept;
    Instruction& operator=(Instruction&& rhs) noexcept;

    ~Instruction();

    void clock();

    bool isDone();

  private:
    uint8_t opcode;
    std::string label;// TODO Use libfmt instead
    InstructionList ops;
    uint8_t clockCount{ 0 };
    uint8_t instructionNum{ 0 };
    interimValue_t interimValue;
};


#endif// ZEMU2_INSTRUCTION_H
