#include "catch2/catch.hpp"

#include "MockBus.h"
#include "CPURegisters.h"
#include "bitUtils.h"

TEST_CASE("16 bit load instructions") {
    MockBus bus;
    auto registers = bus.getCpu().getRegisters();
    SECTION("Load to register pair from parameter") {
        const int requiredClocks = 12;
        const int instructionLength = 3;
        const uint16_t expected = 0x1234U;
        const uint8_t highBytes = 0x12;
        const uint8_t lowBytes = 0x34U;

        bus.write(1, highBytes);
        bus.write(2, lowBytes);
        SECTION("LD BC, d16") {
            const uint8_t opcode = 0x01U;
            bus.write(0, opcode);
            for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }
            CHECK(registers->getPC() == instructionLength);
            CHECK(registers->getBC() == expected);
        }
        SECTION("LD DE, d16") {
            const uint8_t opcode = 0x11U;
            bus.write(0, opcode);
            for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }
            CHECK(registers->getPC() == instructionLength);
            CHECK(registers->getDE() == expected);
        }
        SECTION("LD HL, d16") {
            const uint8_t opcode = 0x21U;
            bus.write(0, opcode);
            for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }
            CHECK(registers->getPC() == instructionLength);
            CHECK(registers->getHL() == expected);
        }
        SECTION("LD SP, d16") {
            const uint8_t opcode = 0x31U;
            bus.write(0, opcode);
            for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }
            CHECK(registers->getPC() == instructionLength);
            CHECK(registers->getSP() == expected);
        }
    }
    SECTION("Stack pointer loads") {
        SECTION("LD (a16), SP") {
            const int requiredClocks = 20;
            const int instructionLength = 3;
            const uint8_t opcode = 0x08U;
            const uint8_t addrHighByte = 0x00;
            const uint8_t addrLowByte = 0x34;
            const uint8_t expected = 0xFAU;

            registers->setSP(expected);
            bus.write(0, opcode);
            bus.write(1, addrHighByte);
            bus.write(2, addrLowByte);

            for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

            CHECK(registers->getPC() == instructionLength);
            CHECK(bus.read(mergeBytes(addrHighByte, addrLowByte)) == expected);
        }
        SECTION("LD HL, SP+r8") {
            const int requiredClocks = 12;
            const int instructionLength = 2;
            const uint8_t opcode = 0xF8U;
            const uint8_t offset = 0x34U;
            const uint16_t initialSP = 0x1200U;
            const uint16_t expected = initialSP + offset;

            registers->setSP(initialSP);
            bus.write(0, opcode);
            bus.write(1, offset);

            for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

            CHECK(registers->getPC() == instructionLength);
            CHECK(registers->getHL() == expected);
        }
        SECTION("LD SP, HL") {
            const int requiredClocks = 8;
            const int instructionLength = 1;
            const uint8_t opcode = 0xF9U;
            const uint16_t expected = 0x1234U;

            registers->setHL(expected);
            bus.write(0, opcode);

            for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

            CHECK(registers->getPC() == instructionLength);
            CHECK(registers->getSP() == expected);
        }
    }
}