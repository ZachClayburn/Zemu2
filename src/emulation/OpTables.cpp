#include "OpTables.h"

#include "Instruction.h"
#include "Operations/DirectLoad.h"
#include "Operations/LoadToRegister.h"
#include "Operations/IndirectLoadFromRegisterPair.h"
#include "Operations/NOP.h"

OpTables::OpTables() {
    //Init with NOPs in every position
    //TODO remove this when all opcodes implemented
    OpcodeFun nopFun = [](IBus *const /*bus*/,
                         CPURegisters *const /*registers*/) {
        return Instruction();
    };
    opTable.fill(nopFun);
    prefixTable.fill(nopFun);
    opTable.at(0) = [](IBus * /*bus*/, CPURegisters * /*registers*/) {
        return Instruction(0, "NOP", { new NOP });
    };
    addBasicLoad(0x06U, LoadToRegister::B, "LD B, d8");
    addBasicLoad(0x0EU, LoadToRegister::C, "LD C, d8");
    addBasicLoad(0x16U, LoadToRegister::D, "LD D, d8");
    addBasicLoad(0x1EU, LoadToRegister::E, "LD E, d8");
    addBasicLoad(0x26U, LoadToRegister::H, "LD H, d8");
    addBasicLoad(0x2EU, LoadToRegister::L, "LD L, d8");
    addBasicLoad(0x3EU, LoadToRegister::A, "LD A, d8");

    addIndirectLoadFromRegisterPair(0x0AU, IndirectLoadFromRegisterPair::BC, LoadToRegister::A, "LD A, (BC)");
    addIndirectLoadFromRegisterPair(0x1AU, IndirectLoadFromRegisterPair::DE, LoadToRegister::A, "LD A, (DE)");
    addIndirectLoadFromRegisterPair(0x2AU, IndirectLoadFromRegisterPair::HLi, LoadToRegister::A, "LD A, (HL+)");
    addIndirectLoadFromRegisterPair(0x3AU, IndirectLoadFromRegisterPair::HLd, LoadToRegister::A, "LD A, (HL-)");
}

OpcodeFun OpTables::operator[](uint8_t opcode) {
    return opTable.at(opcode);
}
void OpTables::addBasicLoad(uint8_t opcode, uint8_t target, const std::string &label) {
    auto targetEnum = static_cast<LoadToRegister::RegisterTarget>(target);
    opTable.at(opcode) = [opcode, label, targetEnum](IBus *bus, CPURegisters *registers) {
        return Instruction(
          opcode,
          label,
          {
            new DirectLoad(bus, registers),
            new LoadToRegister(registers, targetEnum),
          });
    };
}

void OpTables::addIndirectLoadFromRegisterPair(uint8_t opcode, uint8_t fromTarget, uint8_t toTarget, const std::string &label) {
    auto fromTargetEnum = static_cast<IndirectLoadFromRegisterPair::Targets>(fromTarget);
    auto toTargetEnum = static_cast<LoadToRegister::RegisterTarget>(toTarget);
    opTable.at(opcode) = [opcode, label, fromTargetEnum, toTargetEnum](IBus *bus, CPURegisters *registers) {
        return Instruction(
          opcode,
          label,
          {
            new IndirectLoadFromRegisterPair(bus, registers, fromTargetEnum),
            new LoadToRegister(registers, toTargetEnum),
          });
    };
}
