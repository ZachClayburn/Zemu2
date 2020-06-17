#include "Instruction.h"

#include <utility>
#include "Operations/Operation.h"
#include "Operations/NOP.h"

Instruction::Instruction()
  : opcode(0), label("Not implemented!"), ops{new NOP} {}

Instruction::Instruction(uint8_t opcodeIn, std::string labelIn, InstructionList opsIn)
  : opcode{ opcodeIn }, label(std::move(labelIn)), ops(std::move(opsIn)) {}

Instruction::Instruction(Instruction &&old) noexcept
  : opcode{ old.opcode }, label(std::move(old.label)), ops(std::move(old.ops)) {
    old.ops.clear();
}

void Instruction::clock() {
    if (++clockCount < ops.at(instructionNum)->getLength()) {
        return;
    }

    clockCount = 0;
    auto *op = ops.at(instructionNum++);
    auto val = op->operator()(interimValue);
    interimValue = val;
}

bool Instruction::isDone() {
    return instructionNum >= ops.size();
}

Instruction::~Instruction() {
    for (auto &operation : ops) {
        delete operation;
    }
}
Instruction &Instruction::operator=(Instruction &&rhs) noexcept {
    opcode = rhs.opcode;
    label = std::move(rhs.label);
    ops = std::move(rhs.ops);
    clockCount = rhs.clockCount;
    instructionNum = rhs.instructionNum;
    interimValue = rhs.interimValue;

    return *this;
}
