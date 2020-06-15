#include "OpTables.h"
#include "Instruction.h"

OpTables::OpTables() {
    //Init with NOPs in every position
    //TODO remove this when all opcodes implemented
    OpcodeFun nopFun = [](Bus *const /*bus*/,
                    CPURegisters *const /*registers*/) {
        return Instruction();
    };
    opTable.fill(nopFun);
    prefixTable.fill(nopFun);
}

OpcodeFun OpTables::operator[](uint8_t opcode) {
    return opTable.at(opcode);
}
