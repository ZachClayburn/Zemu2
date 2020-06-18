#include "OpTables.h"

#include "Instruction.h"
#include "Operations/DirectLoad.h"
#include "Operations/LoadToRegister.h"
#include "Operations/LoadFromRegister.h"
#include "Operations/IndirectLoadFromRegisterPair.h"
#include "Operations/IndirectLoadToRegisterPair.h"
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
    
    addIndirectLoadFromRegisterPair(0x7EU, IndirectLoadFromRegisterPair::HL, LoadToRegister::A, "LD A, (HL)");
    addIndirectLoadFromRegisterPair(0x46U, IndirectLoadFromRegisterPair::HL, LoadToRegister::B, "LD B, (HL)");
    addIndirectLoadFromRegisterPair(0x4EU, IndirectLoadFromRegisterPair::HL, LoadToRegister::C, "LD C, (HL)");
    addIndirectLoadFromRegisterPair(0x56U, IndirectLoadFromRegisterPair::HL, LoadToRegister::D, "LD D, (HL)");
    addIndirectLoadFromRegisterPair(0x5EU, IndirectLoadFromRegisterPair::HL, LoadToRegister::E, "LD E, (HL)");
    addIndirectLoadFromRegisterPair(0x66U, IndirectLoadFromRegisterPair::HL, LoadToRegister::H, "LD H, (HL)");
    addIndirectLoadFromRegisterPair(0x6EU, IndirectLoadFromRegisterPair::HL, LoadToRegister::L, "LD L, (HL)");
    
    addIndirectLoadToRegisterPair(0x02U, LoadToRegister::A, IndirectLoadToRegisterPair::BC, "LD (BC), A");
    addIndirectLoadToRegisterPair(0x12U, LoadToRegister::A, IndirectLoadToRegisterPair::DE, "LD (DE), A");
    addIndirectLoadToRegisterPair(0x22U, LoadToRegister::A, IndirectLoadToRegisterPair::HLi, "LD (HL+), A");
    addIndirectLoadToRegisterPair(0x32U, LoadToRegister::A, IndirectLoadToRegisterPair::HLd, "LD (HL-), A");
    addIndirectLoadToRegisterPair(0x77U, LoadToRegister::A, IndirectLoadToRegisterPair::HL, "LD (HL), A");
    addIndirectLoadToRegisterPair(0x70U, LoadToRegister::B, IndirectLoadToRegisterPair::HL, "LD (HL), B");
    addIndirectLoadToRegisterPair(0x71U, LoadToRegister::C, IndirectLoadToRegisterPair::HL, "LD (HL), C");
    addIndirectLoadToRegisterPair(0x72U, LoadToRegister::D, IndirectLoadToRegisterPair::HL, "LD (HL), D");
    addIndirectLoadToRegisterPair(0x73U, LoadToRegister::E, IndirectLoadToRegisterPair::HL, "LD (HL), E");
    addIndirectLoadToRegisterPair(0x74U, LoadToRegister::H, IndirectLoadToRegisterPair::HL, "LD (HL), H");
    addIndirectLoadToRegisterPair(0x75U, LoadToRegister::L, IndirectLoadToRegisterPair::HL, "LD (HL), L");
    
    opTable.at(0x36U) = [](IBus* bus, CPURegisters *registers) {
        return Instruction(
          0x36U,
          "LD (HL), d8",
          {
            new DirectLoad(bus, registers),
            new IndirectLoadToRegisterPair(bus, registers, IndirectLoadToRegisterPair::HL),
          });
    };
}

OpcodeFun OpTables::operator[](uint8_t opcode) {
    return opTable.at(opcode);
}
void OpTables::addBasicLoad(uint8_t opcode, uint8_t target, const std::string &label) {
    auto targetEnum = static_cast<LoadToRegister::Targets>(target);
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
    auto toTargetEnum = static_cast<LoadToRegister::Targets>(toTarget);
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

void OpTables::addIndirectLoadToRegisterPair(uint8_t opcode, uint8_t fromTarget, uint8_t toTarget, const std::string &label) {
    auto fromTargetEnum = static_cast<LoadFromRegister::Targets>(fromTarget);
    auto toTargetEnum = static_cast<IndirectLoadToRegisterPair::Targets>(toTarget);
    opTable.at(opcode) = [opcode, label, fromTargetEnum, toTargetEnum](IBus *bus, CPURegisters *registers) {
           return Instruction(
             opcode,
             label,
             {
               new LoadFromRegister(registers, fromTargetEnum),
               new IndirectLoadToRegisterPair(bus, registers, toTargetEnum),
             });
    };
}
