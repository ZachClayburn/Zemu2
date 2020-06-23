#include "catch2/catch.hpp"

#include "MockBus.h"
#include "CPURegisters.h"

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
}