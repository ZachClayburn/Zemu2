#include "catch2/catch.hpp"

#include "MockBus.h"
#include "CPURegisters.h"
#include "bitUtils.h"

TEST_CASE("8 bit arithmetic instructions") {
    MockBus bus;
    auto registers = bus.getCpu().getRegisters();
    const int instructionLength = 1;
    SECTION("INC and DEC") {
        SECTION("Registers are correctly modified") {
            const int requiredClocks = 4;
            const uint8_t initialValue = 0xAFU;
            SECTION("Increment") {
                const uint8_t expectedValue = initialValue + 1;
                SECTION("INC B") {
                    const uint8_t opcode = 0x04U;
                    registers->setB(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getB() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("INC D") {
                    const uint8_t opcode = 0x14U;
                    registers->setD(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getD() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("INC H") {
                    const uint8_t opcode = 0x24U;
                    registers->setH(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getH() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("INC C") {
                    const uint8_t opcode = 0x0CU;
                    registers->setC(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getC() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("INC E") {
                    const uint8_t opcode = 0x1CU;
                    registers->setE(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getE() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("INC L") {
                    const uint8_t opcode = 0x2CU;
                    registers->setL(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getL() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("INC A") {
                    const uint8_t opcode = 0x3CU;
                    registers->setA(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getA() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
            }
            SECTION("Decrement") {
                const uint8_t expectedValue = initialValue - 1;
                SECTION("DEC B") {
                    const uint8_t opcode = 0x05U;
                    registers->setB(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getB() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("DEC D") {
                    const uint8_t opcode = 0x15U;
                    registers->setD(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getD() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("DEC H") {
                    const uint8_t opcode = 0x25U;
                    registers->setH(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getH() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("DEC C") {
                    const uint8_t opcode = 0x0DU;
                    registers->setC(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getC() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("DEC E") {
                    const uint8_t opcode = 0x1DU;
                    registers->setE(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getE() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("DEC L") {
                    const uint8_t opcode = 0x2DU;
                    registers->setL(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getL() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("DEC A") {
                    const uint8_t opcode = 0x3DU;
                    registers->setA(initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getA() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
            }
        }
        SECTION("Flags are properly set") {
            const int requiredClocks = 4;
            SECTION("Increment") {
                const uint8_t opcode = 0x3CU;
                SECTION("Z set") {
                    const uint8_t initialValue = 0xFFU;

                    bus.write(0, opcode);
                    registers->setA(initialValue);
                    registers->setZFlag(false);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    REQUIRE(registers->checkZFlag());
                }
                SECTION("N set") {
                    const uint8_t initialValue = 0x0FU;

                    bus.write(0, opcode);
                    registers->setA(initialValue);
                    registers->setNFlag(true);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    REQUIRE_FALSE(registers->checkNFlag());
                }
                SECTION("H set") {
                    const uint8_t initialValue = 0x0FU;

                    bus.write(0, opcode);
                    registers->setA(initialValue);
                    registers->setHFlag(false);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    REQUIRE(registers->checkHFlag());
                }
            }
            SECTION("Decrement") {
                const uint8_t opcode = 0x3DU;
                SECTION("Z set") {
                    const uint8_t initialValue = 0x01U;

                    bus.write(0, opcode);
                    registers->setA(initialValue);
                    registers->setZFlag(false);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    REQUIRE(registers->checkZFlag());
                }
                SECTION("N set") {
                    const uint8_t initialValue = 0x0FU;

                    bus.write(0, opcode);
                    registers->setA(initialValue);
                    registers->setNFlag(true);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    REQUIRE(registers->checkNFlag());
                }
                SECTION("H set") {
                    const uint8_t initialValue = 0xF0U;

                    bus.write(0, opcode);
                    registers->setA(initialValue);
                    registers->setHFlag(false);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    REQUIRE(registers->checkHFlag());
                }
            }
        }
        SECTION("Indirect increments & decrements") {
            const int requiredClocks = 12;
            const uint16_t addr = 0x000FU;
            SECTION("INC (HL)") {
                const uint8_t opcode = 0x34U;
                SECTION("Values are correct") {
                    const uint16_t initialValue = 0xAFU;
                    const uint16_t expectedValue = 0xAF - 1;

                    registers->setHL(addr);
                    bus.write(addr, initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getHL() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("Flags are correct") {
                    SECTION("Z set") {
                        const uint8_t initialValue = 0xFFU;

                        bus.write(0, opcode);
                        registers->setHL(addr);
                        bus.write(addr, initialValue);
                        registers->setZFlag(false);

                        for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                        REQUIRE(registers->checkZFlag());
                    }
                    SECTION("N set") {
                        const uint8_t initialValue = 0x0FU;

                        bus.write(0, opcode);
                        registers->setHL(addr);
                        bus.write(addr, initialValue);
                        registers->setNFlag(true);

                        for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                        REQUIRE_FALSE(registers->checkNFlag());
                    }
                    SECTION("H set") {
                        const uint8_t initialValue = 0x0FU;

                        bus.write(0, opcode);
                        registers->setHL(addr);
                        bus.write(addr, initialValue);
                        registers->setHFlag(false);

                        for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                        REQUIRE(registers->checkHFlag());
                    }
                }
            }
            SECTION("DEC (HL)") {
                const uint8_t opcode = 0x35U;
                SECTION("Values are correct") {
                    const uint16_t initialValue = 0xAFU;
                    const uint16_t expectedValue = 0xAF - 1;

                    registers->setHL(addr);
                    bus.write(addr, initialValue);
                    bus.write(0, opcode);

                    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                    CHECK(registers->getHL() == expectedValue);
                    CHECK(registers->getPC() == instructionLength);
                }
                SECTION("Flags are correct") {
                    SECTION("Z set") {
                        const uint8_t initialValue = 0x01U;

                        bus.write(0, opcode);
                        registers->setHL(addr);
                        bus.write(addr, initialValue);
                        registers->setZFlag(false);

                        for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                        REQUIRE(registers->checkZFlag());
                    }
                    SECTION("N set") {
                        const uint8_t initialValue = 0x0FU;

                        bus.write(0, opcode);
                        registers->setHL(addr);
                        bus.write(addr, initialValue);
                        registers->setNFlag(true);

                        for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                        REQUIRE(registers->checkNFlag());
                    }
                    SECTION("H set") {
                        const uint8_t initialValue = 0xF0U;

                        bus.write(0, opcode);
                        registers->setHL(addr);
                        bus.write(addr, initialValue);
                        registers->setHFlag(false);

                        for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }

                        REQUIRE(registers->checkHFlag());
                    }

                }
            }
        }
    }
}