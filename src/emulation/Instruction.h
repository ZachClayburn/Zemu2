#ifndef ZEMU2_INSTRUCTION_H
#define ZEMU2_INSTRUCTION_H

#include <cstdint>
#include <string>
#include <vector>
#include <optional>
#include "Operation.h"

class Instruction
{
  public:
    Instruction();

    Instruction(uint8_t opcode, std::string label, std::vector<Operation> ops);

    std::optional<Operation> clock();

  private:
    uint8_t opcode;
    std::string label;//TODO Use libfmt instead
    std::vector<Operation> ops;//TODO If I am going to use polymorphism, this needs to be pointers...
    uint8_t clockCount{ 0 };
    uint8_t instructionNum{ 0 };
};


#endif//ZEMU2_INSTRUCTION_H
