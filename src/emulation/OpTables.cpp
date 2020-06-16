#include "OpTables.h"

#include "Instruction.h"
#include "Operations/DirectLoad.h"
#include "Operations/LoadToRegister.h"

OpTables::OpTables() {
    //Init with NOPs in every position
    //TODO remove this when all opcodes implemented
    OpcodeFun nopFun = [](IBus *const /*bus*/,
                         CPURegisters *const /*registers*/) {
        return Instruction();
    };
    opTable.fill(nopFun);
    prefixTable.fill(nopFun);
    
    addBasicLoad(0x06U, LoadToRegister::B, "LD B, d8");
    addBasicLoad(0x0EU, LoadToRegister::C, "LD C, d8");
    addBasicLoad(0x16U, LoadToRegister::D, "LD D, d8");
    addBasicLoad(0x1EU, LoadToRegister::E, "LD E, d8");
    addBasicLoad(0x26U, LoadToRegister::H, "LD H, d8");
    addBasicLoad(0x2EU, LoadToRegister::L, "LD L, d8");
    addBasicLoad(0x3EU, LoadToRegister::A, "LD A, d8");

}

OpcodeFun OpTables::operator[](uint8_t opcode) {
    return opTable.at(opcode);
}
void OpTables::addBasicLoad(uint8_t opcode, uint8_t target, const std::string& label) {
    auto targetEnum = static_cast<LoadToRegister::RegisterTarget>(target);
    opTable.at(opcode) = [opcode, label, targetEnum](IBus *bus, CPURegisters *registers) {
           Instruction i(
             opcode,
             label,
             {
               new DirectLoad(bus, registers),
               new LoadToRegister(registers, targetEnum),
             });
           return i;
    };
    
}
