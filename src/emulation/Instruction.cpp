#include "Instruction.h"

#include <utility>

Instruction::Instruction()
  : opcode(0), label("Not implemented!") {}

Instruction::Instruction(uint8_t opcode, std::string label, std::vector<Operation> ops)
  : opcode{ opcode }, label(std::move(label)), ops(std::move(ops)) {}

std::optional<Operation> Instruction::clock() {
    if (++clockCount < ops.at(instructionNum).getLength()) {
        return std::nullopt;
    }
    
    clockCount = 0;
    return std::make_optional(ops.at(instructionNum++));
}
