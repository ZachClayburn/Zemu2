#include "OpTables.h"

#include "Instruction.h"
#include "Operations/DirectLoad.h"
#include "Operations/DirectLoadAndAddAsSigned.h"
#include "Operations/LoadToRegister.h"
#include "Operations/LoadFromRegister.h"
#include "Operations/IndirectLoadFromRegisterPair.h"
#include "Operations/IndirectLoadToRegisterPair.h"
#include "Operations/NOP.h"
#include "Operations/IndirectLoadFromParameter.h"
#include "Operations/IndirectLoadToParameter.h"
#include "Operations/IndirectLoadToParameterAndPlusOne.h"
#include "Operations/IndirectLoadFromPrefixAndCRegister.h"
#include "Operations/IndirectLoadToPrefixAndCRegister.h"
#include "Operations/IndirectLoadToPrefixAndParameter.h"
#include "Operations/IndirectLoadFromPrefixAndParameter.h"
#include "Operations/LoadToRegisterPair.h"
#include "Operations/LoadFromRegisterPair.h"
#include "Operations/DirectExtendedLoad.h"
#include "Operations/Push.h"
#include "Operations/Pop.h"

static void addLoadToRegisterPair(std::array<OpcodeFun, 256>& opTable,
  uint8_t opCode,
  LoadToRegisterPair::Targets target,
  const std::string& label) {
    opTable.at(opCode) = [opCode, label, target](IBus* bus, CPURegisters* registers) {
        return Instruction(opCode,
          label,
          {
            new DirectExtendedLoad(bus, registers),
            new LoadToRegisterPair(registers, target),
          });
    };
}

static void addPush(std::array<OpcodeFun, 256>& opTable,
  uint8_t opCode,
  const std::string& label,
  Push::Target target) {
    opTable.at(opCode) = [opCode, label, target](IBus* bus, CPURegisters* registers) {
        return Instruction(opCode, label, { new Push(bus, registers, target) });
    };
}

static void addPop(std::array<OpcodeFun, 256>& opTable,
  uint8_t opCode,
  const std::string& label,
  Pop::Target target) {
    opTable.at(opCode) = [opCode, label, target](IBus* bus, CPURegisters* registers) {
        return Instruction(opCode, label, { new Pop(bus, registers, target) });
    };
}

OpTables::OpTables() {
    // Init with NOPs in every position
    // TODO remove this when all opcodes implemented
    OpcodeFun nopFun = [](IBus* const /*bus*/, CPURegisters* const /*registers*/) {
        return Instruction();
    };
    opTable.fill(nopFun);
    prefixTable.fill(nopFun);
    opTable.at(0) = [](IBus* /*bus*/, CPURegisters* /*registers*/) {
        return Instruction(0, "NOP", { new NOP });
    };
    addBasicLoad(0x06U, LoadToRegister::B, "LD B, d8");
    addBasicLoad(0x0EU, LoadToRegister::C, "LD C, d8");
    addBasicLoad(0x16U, LoadToRegister::D, "LD D, d8");
    addBasicLoad(0x1EU, LoadToRegister::E, "LD E, d8");
    addBasicLoad(0x26U, LoadToRegister::H, "LD H, d8");
    addBasicLoad(0x2EU, LoadToRegister::L, "LD L, d8");
    addBasicLoad(0x3EU, LoadToRegister::A, "LD A, d8");

    addIndirectLoadFromRegisterPair(
      0x0AU, IndirectLoadFromRegisterPair::BC, LoadToRegister::A, "LD A, (BC)");
    addIndirectLoadFromRegisterPair(
      0x1AU, IndirectLoadFromRegisterPair::DE, LoadToRegister::A, "LD A, (DE)");
    addIndirectLoadFromRegisterPair(
      0x2AU, IndirectLoadFromRegisterPair::HLi, LoadToRegister::A, "LD A, (HL+)");
    addIndirectLoadFromRegisterPair(
      0x3AU, IndirectLoadFromRegisterPair::HLd, LoadToRegister::A, "LD A, (HL-)");

    addIndirectLoadFromRegisterPair(
      0x7EU, IndirectLoadFromRegisterPair::HL, LoadToRegister::A, "LD A, (HL)");
    addIndirectLoadFromRegisterPair(
      0x46U, IndirectLoadFromRegisterPair::HL, LoadToRegister::B, "LD B, (HL)");
    addIndirectLoadFromRegisterPair(
      0x4EU, IndirectLoadFromRegisterPair::HL, LoadToRegister::C, "LD C, (HL)");
    addIndirectLoadFromRegisterPair(
      0x56U, IndirectLoadFromRegisterPair::HL, LoadToRegister::D, "LD D, (HL)");
    addIndirectLoadFromRegisterPair(
      0x5EU, IndirectLoadFromRegisterPair::HL, LoadToRegister::E, "LD E, (HL)");
    addIndirectLoadFromRegisterPair(
      0x66U, IndirectLoadFromRegisterPair::HL, LoadToRegister::H, "LD H, (HL)");
    addIndirectLoadFromRegisterPair(
      0x6EU, IndirectLoadFromRegisterPair::HL, LoadToRegister::L, "LD L, (HL)");

    addIndirectLoadToRegisterPair(
      0x02U, LoadToRegister::A, IndirectLoadToRegisterPair::BC, "LD (BC), A");
    addIndirectLoadToRegisterPair(
      0x12U, LoadToRegister::A, IndirectLoadToRegisterPair::DE, "LD (DE), A");
    addIndirectLoadToRegisterPair(
      0x22U, LoadToRegister::A, IndirectLoadToRegisterPair::HLi, "LD (HL+), A");
    addIndirectLoadToRegisterPair(
      0x32U, LoadToRegister::A, IndirectLoadToRegisterPair::HLd, "LD (HL-), A");
    addIndirectLoadToRegisterPair(
      0x77U, LoadToRegister::A, IndirectLoadToRegisterPair::HL, "LD (HL), A");
    addIndirectLoadToRegisterPair(
      0x70U, LoadToRegister::B, IndirectLoadToRegisterPair::HL, "LD (HL), B");
    addIndirectLoadToRegisterPair(
      0x71U, LoadToRegister::C, IndirectLoadToRegisterPair::HL, "LD (HL), C");
    addIndirectLoadToRegisterPair(
      0x72U, LoadToRegister::D, IndirectLoadToRegisterPair::HL, "LD (HL), D");
    addIndirectLoadToRegisterPair(
      0x73U, LoadToRegister::E, IndirectLoadToRegisterPair::HL, "LD (HL), E");
    addIndirectLoadToRegisterPair(
      0x74U, LoadToRegister::H, IndirectLoadToRegisterPair::HL, "LD (HL), H");
    addIndirectLoadToRegisterPair(
      0x75U, LoadToRegister::L, IndirectLoadToRegisterPair::HL, "LD (HL), L");

    addRegisterToRegisterLoad(0x40U, LoadFromRegister::B, LoadToRegister::B, "LD B, B");
    addRegisterToRegisterLoad(0x41U, LoadFromRegister::C, LoadToRegister::B, "LD B, C");
    addRegisterToRegisterLoad(0x42U, LoadFromRegister::D, LoadToRegister::B, "LD B, D");
    addRegisterToRegisterLoad(0x43U, LoadFromRegister::E, LoadToRegister::B, "LD B, E");
    addRegisterToRegisterLoad(0x44U, LoadFromRegister::H, LoadToRegister::B, "LD B, H");
    addRegisterToRegisterLoad(0x45U, LoadFromRegister::L, LoadToRegister::B, "LD B, L");
    addRegisterToRegisterLoad(0x47U, LoadFromRegister::A, LoadToRegister::B, "LD B, A");

    addRegisterToRegisterLoad(0x50U, LoadFromRegister::B, LoadToRegister::D, "LD D, B");
    addRegisterToRegisterLoad(0x51U, LoadFromRegister::C, LoadToRegister::D, "LD D, C");
    addRegisterToRegisterLoad(0x52U, LoadFromRegister::D, LoadToRegister::D, "LD D, D");
    addRegisterToRegisterLoad(0x53U, LoadFromRegister::E, LoadToRegister::D, "LD D, E");
    addRegisterToRegisterLoad(0x54U, LoadFromRegister::H, LoadToRegister::D, "LD D, H");
    addRegisterToRegisterLoad(0x55U, LoadFromRegister::L, LoadToRegister::D, "LD D, L");
    addRegisterToRegisterLoad(0x57U, LoadFromRegister::A, LoadToRegister::D, "LD D, A");

    addRegisterToRegisterLoad(0x60U, LoadFromRegister::B, LoadToRegister::H, "LD H, B");
    addRegisterToRegisterLoad(0x61U, LoadFromRegister::C, LoadToRegister::H, "LD H, C");
    addRegisterToRegisterLoad(0x62U, LoadFromRegister::D, LoadToRegister::H, "LD H, D");
    addRegisterToRegisterLoad(0x63U, LoadFromRegister::E, LoadToRegister::H, "LD H, E");
    addRegisterToRegisterLoad(0x64U, LoadFromRegister::H, LoadToRegister::H, "LD H, H");
    addRegisterToRegisterLoad(0x65U, LoadFromRegister::L, LoadToRegister::H, "LD H, L");
    addRegisterToRegisterLoad(0x6AU, LoadFromRegister::A, LoadToRegister::H, "LD H, A");

    addRegisterToRegisterLoad(0x60U, LoadFromRegister::B, LoadToRegister::H, "LD H, B");
    addRegisterToRegisterLoad(0x61U, LoadFromRegister::C, LoadToRegister::H, "LD H, C");
    addRegisterToRegisterLoad(0x62U, LoadFromRegister::D, LoadToRegister::H, "LD H, D");
    addRegisterToRegisterLoad(0x63U, LoadFromRegister::E, LoadToRegister::H, "LD H, E");
    addRegisterToRegisterLoad(0x64U, LoadFromRegister::H, LoadToRegister::H, "LD H, H");
    addRegisterToRegisterLoad(0x65U, LoadFromRegister::L, LoadToRegister::H, "LD H, L");
    addRegisterToRegisterLoad(0x67U, LoadFromRegister::A, LoadToRegister::H, "LD H, A");

    addRegisterToRegisterLoad(0x48U, LoadFromRegister::B, LoadToRegister::C, "LD C, B");
    addRegisterToRegisterLoad(0x49U, LoadFromRegister::C, LoadToRegister::C, "LD C, C");
    addRegisterToRegisterLoad(0x4AU, LoadFromRegister::D, LoadToRegister::C, "LD C, D");
    addRegisterToRegisterLoad(0x4BU, LoadFromRegister::E, LoadToRegister::C, "LD C, E");
    addRegisterToRegisterLoad(0x4CU, LoadFromRegister::H, LoadToRegister::C, "LD C, H");
    addRegisterToRegisterLoad(0x4DU, LoadFromRegister::L, LoadToRegister::C, "LD C, L");
    addRegisterToRegisterLoad(0x4FU, LoadFromRegister::A, LoadToRegister::C, "LD C, A");

    addRegisterToRegisterLoad(0x58U, LoadFromRegister::B, LoadToRegister::E, "LD E, B");
    addRegisterToRegisterLoad(0x59U, LoadFromRegister::C, LoadToRegister::E, "LD E, C");
    addRegisterToRegisterLoad(0x5AU, LoadFromRegister::D, LoadToRegister::E, "LD E, D");
    addRegisterToRegisterLoad(0x5BU, LoadFromRegister::E, LoadToRegister::E, "LD E, E");
    addRegisterToRegisterLoad(0x5CU, LoadFromRegister::H, LoadToRegister::E, "LD E, H");
    addRegisterToRegisterLoad(0x5DU, LoadFromRegister::L, LoadToRegister::E, "LD E, L");
    addRegisterToRegisterLoad(0x5FU, LoadFromRegister::A, LoadToRegister::E, "LD E, A");

    addRegisterToRegisterLoad(0x68U, LoadFromRegister::B, LoadToRegister::L, "LD L, B");
    addRegisterToRegisterLoad(0x69U, LoadFromRegister::C, LoadToRegister::L, "LD L, C");
    addRegisterToRegisterLoad(0x6AU, LoadFromRegister::D, LoadToRegister::L, "LD L, D");
    addRegisterToRegisterLoad(0x6BU, LoadFromRegister::E, LoadToRegister::L, "LD L, E");
    addRegisterToRegisterLoad(0x6CU, LoadFromRegister::H, LoadToRegister::L, "LD L, H");
    addRegisterToRegisterLoad(0x6DU, LoadFromRegister::L, LoadToRegister::L, "LD L, L");
    addRegisterToRegisterLoad(0x6FU, LoadFromRegister::A, LoadToRegister::L, "LD L, A");

    addRegisterToRegisterLoad(0x78U, LoadFromRegister::B, LoadToRegister::A, "LD A, B");
    addRegisterToRegisterLoad(0x79U, LoadFromRegister::C, LoadToRegister::A, "LD A, C");
    addRegisterToRegisterLoad(0x7AU, LoadFromRegister::D, LoadToRegister::A, "LD A, D");
    addRegisterToRegisterLoad(0x7BU, LoadFromRegister::E, LoadToRegister::A, "LD A, E");
    addRegisterToRegisterLoad(0x7CU, LoadFromRegister::H, LoadToRegister::A, "LD A, H");
    addRegisterToRegisterLoad(0x7DU, LoadFromRegister::L, LoadToRegister::A, "LD A, L");
    addRegisterToRegisterLoad(0x7FU, LoadFromRegister::A, LoadToRegister::A, "LD A, A");

    addPush(opTable, 0xC5U, "PUSH BC", Push::BC);
    addPush(opTable, 0xD5U, "PUSH DE", Push::DE);
    addPush(opTable, 0xE5U, "PUSH HL", Push::HL);
    addPush(opTable, 0xF5U, "PUSH AF", Push::AF);

    addPop(opTable, 0xC1U, "PUSH BC", Pop::BC);
    addPop(opTable, 0xD1U, "PUSH DE", Pop::DE);
    addPop(opTable, 0xE1U, "PUSH HL", Pop::HL);
    addPop(opTable, 0xF1U, "PUSH AF", Pop::AF);

    opTable.at(0x36U) = [](IBus* bus, CPURegisters* registers) {
        return Instruction(0x36U,
          "LD (HL), d8",
          {
            new DirectLoad(bus, registers),
            new IndirectLoadToRegisterPair(bus, registers, IndirectLoadToRegisterPair::HL),
          });
    };

    opTable.at(0xFAU) = [](IBus* bus, CPURegisters* registers) {
        return Instruction(0xFAU,
          "LD A, (a16)",
          {
            new IndirectLoadFromParameter(bus, registers),
            new LoadToRegister(registers, LoadToRegister::A),
          });
    };
    opTable.at(0xEAU) = [](IBus* bus, CPURegisters* registers) {
        return Instruction(0xEAU,
          "LD (a16), A",
          {
            new LoadFromRegister(registers, LoadFromRegister::A),
            new IndirectLoadToParameter(bus, registers),
          });
    };
    opTable.at(0xE2U) = [](IBus* bus, CPURegisters* registers) {
        return Instruction(0xE2U,
          "LD (C), A",
          {
            new LoadFromRegister(registers, LoadFromRegister::A),
            new IndirectLoadToPrefixAndCRegister(bus, registers),
          });
    };
    opTable.at(0xF2U) = [](IBus* bus, CPURegisters* registers) {
        return Instruction(0xF2U,
          "LD A, (C)",
          {
            new IndirectLoadFromPrefixAndCRegister(bus, registers),
            new LoadToRegister(registers, LoadToRegister::A),
          });
    };
    opTable.at(0xE0U) = [](IBus* bus, CPURegisters* registers) {
        return Instruction(0xE0U,
          "LD (a8), A",
          {
            new LoadFromRegister(registers, LoadFromRegister::A),
            new IndirectLoadToPrefixAndParameter(bus, registers),
          });
    };
    opTable.at(0xF0U) = [](IBus* bus, CPURegisters* registers) {
        return Instruction(0xF0U,
          "LD A, (a8)",
          {
            new IndirectLoadFromPrefixAndParameter(bus, registers),
            new LoadToRegister(registers, LoadToRegister::A),
          });
    };
    addLoadToRegisterPair(opTable, 0x01, LoadToRegisterPair::BC, "LD BC, d16");
    addLoadToRegisterPair(opTable, 0x11, LoadToRegisterPair::DE, "LD DE, d16");
    addLoadToRegisterPair(opTable, 0x21, LoadToRegisterPair::HL, "LD HL, d16");
    addLoadToRegisterPair(opTable, 0x31, LoadToRegisterPair::SP, "LD SP, d16");

    opTable.at(0x08U) = [](IBus* bus, CPURegisters* registers) {
        return Instruction(0x08U,
          "LD (a16), SP",
          {
            new LoadFromRegisterPair(registers, LoadFromRegisterPair::SP),
            new IndirectLoadToParameterAndPlusOne(bus, registers),
          });
    };

    opTable.at(0xF8U) = [](IBus* bus, CPURegisters* registers) {
        return Instruction(0xF8U,
          "LD HL, SP + r8",
          {
            new LoadFromRegisterPair(registers, LoadFromRegisterPair::SP),
            new DirectLoadAndAddAsSigned(bus, registers),
            new LoadToRegisterPair(registers, LoadToRegisterPair::HL),
          });
    };

    opTable.at(0xF9U) = [](IBus* /*bus*/, CPURegisters* registers) {
        return Instruction(0xF9U,
          "LD SP, HL",
          {
            new LoadFromRegisterPair(registers, LoadFromRegisterPair::HL),
            new LoadToRegisterPair(registers, LoadToRegisterPair::SP),
          });
    };
}

OpcodeFun OpTables::operator[](uint8_t opcode) { return opTable.at(opcode); }
void OpTables::addBasicLoad(uint8_t opcode, uint8_t target, const std::string& label) {
    auto targetEnum = static_cast<LoadToRegister::Targets>(target);
    opTable.at(opcode) = [opcode, label, targetEnum](IBus* bus, CPURegisters* registers) {
        return Instruction(opcode,
          label,
          {
            new DirectLoad(bus, registers),
            new LoadToRegister(registers, targetEnum),
          });
    };
}

void OpTables::addIndirectLoadFromRegisterPair(uint8_t opcode,
  uint8_t fromTarget,
  uint8_t toTarget,
  const std::string& label) {
    auto fromTargetEnum = static_cast<IndirectLoadFromRegisterPair::Targets>(fromTarget);
    auto toTargetEnum = static_cast<LoadToRegister::Targets>(toTarget);
    opTable.at(opcode) = [opcode, label, fromTargetEnum, toTargetEnum](
                           IBus* bus, CPURegisters* registers) {
        return Instruction(opcode,
          label,
          {
            new IndirectLoadFromRegisterPair(bus, registers, fromTargetEnum),
            new LoadToRegister(registers, toTargetEnum),
          });
    };
}

void OpTables::addIndirectLoadToRegisterPair(uint8_t opcode,
  uint8_t fromTarget,
  uint8_t toTarget,
  const std::string& label) {
    auto fromTargetEnum = static_cast<LoadFromRegister::Targets>(fromTarget);
    auto toTargetEnum = static_cast<IndirectLoadToRegisterPair::Targets>(toTarget);
    opTable.at(opcode) = [opcode, label, fromTargetEnum, toTargetEnum](
                           IBus* bus, CPURegisters* registers) {
        return Instruction(opcode,
          label,
          {
            new LoadFromRegister(registers, fromTargetEnum),
            new IndirectLoadToRegisterPair(bus, registers, toTargetEnum),
          });
    };
}

void OpTables::addRegisterToRegisterLoad(uint8_t opcode,
  uint8_t fromTarget,
  uint8_t toTarget,
  const std::string& label) {
    auto fromTargetEnum = static_cast<LoadFromRegister::Targets>(fromTarget);
    auto toTargetEnum = static_cast<LoadToRegister::Targets>(toTarget);
    opTable.at(opcode) = [opcode, label, fromTargetEnum, toTargetEnum](
                           IBus* /*bus*/, CPURegisters* registers) {
        return Instruction(opcode,
          label,
          {
            new LoadFromRegister(registers, fromTargetEnum),
            new LoadToRegister(registers, toTargetEnum),
          });
    };
}
