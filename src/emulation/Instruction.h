#ifndef ZEMU2_INSTRUCTION_H
#define ZEMU2_INSTRUCTION_H

#include <cstdint>
#include <string>
#include <vector>
#include <variant>

class Operation;

class Instruction
{
  public:
    Instruction();

    Instruction(uint8_t opcodeIn, std::string labelIn, std::vector<Operation *> opsIn);

    void clock();

    bool isDone();

  private:
    uint8_t opcode;
    std::string label;//TODO Use libfmt instead
    std::vector<Operation *> ops;//TODO Make this a managed pointer? Just reference a constant Operation?
    uint8_t clockCount{ 0 };
    uint8_t instructionNum{ 0 };
    std::variant<uint8_t, uint16_t> interimValue{ static_cast<uint16_t>(0) };
};


#endif//ZEMU2_INSTRUCTION_H
