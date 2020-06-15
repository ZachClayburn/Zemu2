#include "Instruction.h"

#include <utility>
#include "Operation.h"

Instruction::Instruction()
  : opcode(0), label("Not implemented!") {}

Instruction::Instruction(uint8_t opcodeIn, std::string labelIn, std::vector<Operation*> opsIn)
  : opcode{ opcodeIn }, label(std::move(labelIn)), ops(std::move(opsIn)) {}

std::optional<Operation*> Instruction::clock() {
    if (++clockCount < ops.at(instructionNum)->getLength()) {
        return std::nullopt;
    }
    
    clockCount = 0;
    return std::make_optional(ops.at(instructionNum++));
}

bool Instruction::isDone() {
    return instructionNum >= ops.size();
}
