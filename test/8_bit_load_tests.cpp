#include <catch2/catch.hpp>

#include <functional>
#include "MockBus.h"
#include "CPURegisters.h"

void testBasicLoad(MockBus& bus,
  uint8_t opcode,
  int requiredClocks,
  uint8_t expected,
  const std::function<uint8_t(void)>& getterFun) {
    bus.write(0x00, opcode);
    for (int i = 0; i < requiredClocks; ++i) { bus.clock(); }
    REQUIRE(getterFun() == expected);
}

void testRegisterToRegisterLoad(MockBus& bus,
  CPURegisters* registers,
  uint8_t opcode,
  char from,
  char to) {

    const uint8_t expected = 0x4AU;
    switch (from) {
    case 'A':
        registers->setA(expected);
        break;
    case 'B':
        registers->setB(expected);
        break;
    case 'C':
        registers->setC(expected);
        break;
    case 'D':
        registers->setD(expected);
        break;
    case 'E':
        registers->setE(expected);
        break;
    case 'H':
        registers->setH(expected);
        break;
    case 'L':
        registers->setL(expected);
        break;
    default:
        throw std::invalid_argument("Bad from argument");
    }

    bus.write(0, opcode);
    for (int i = 0; i < 4; i++) { bus.clock(); }

    switch (to) {
    case 'A':
        REQUIRE(registers->getA() == expected);
        break;
    case 'B':
        REQUIRE(registers->getB() == expected);
        break;
    case 'C':
        REQUIRE(registers->getC() == expected);
        break;
    case 'D':
        REQUIRE(registers->getD() == expected);
        break;
    case 'E':
        REQUIRE(registers->getE() == expected);
        break;
    case 'H':
        REQUIRE(registers->getH() == expected);
        break;
    case 'L':
        REQUIRE(registers->getL() == expected);
        break;
    default:
        throw std::invalid_argument("Bad to argument");
    }
}

TEST_CASE("8 bit load instructions") {
    MockBus bus;
    auto registers = bus.getCpu().getRegisters();
    const uint8_t expected = 0x4AU;
    SECTION("direct 8 bit load from parameter") {
        bus.write(0x01, expected);
        const int requiredClocks = 8;
        SECTION("LD A, d8") {
            const uint8_t opcode = 0x3EU;
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [registers]() { return registers->getA(); });
        }
        SECTION("LD B, d8") {
            const uint8_t opcode = 0x06U;
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [registers]() { return registers->getB(); });
        }
        SECTION("LD C, d8") {
            const uint8_t opcode = 0x0EU;
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [registers]() { return registers->getC(); });
        }
        SECTION("LD D, d8") {
            const uint8_t opcode = 0x16U;
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [registers]() { return registers->getD(); });
        }
        SECTION("LD E, d8") {
            const uint8_t opcode = 0x1EU;
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [registers]() { return registers->getE(); });
        }
        SECTION("LD H, d8") {
            const uint8_t opcode = 0x26U;
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [registers]() { return registers->getH(); });
        }
        SECTION("LD L, d8") {
            const uint8_t opcode = 0x2EU;
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [registers]() { return registers->getL(); });
        }
    }
    SECTION("Indirect load instructions") {
        const uint16_t address = 0x4A4AU;
        SECTION("Load from A") {
            const int requiredClocks = 8;
            registers->setA(expected);
            SECTION("LD (BC), A") {
                const uint8_t opcode = 0x02U;
                registers->setBC(address);
                testBasicLoad(
                  bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (DE), A") {
                const uint8_t opcode = 0x12U;
                registers->setDE(address);
                testBasicLoad(
                  bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (HL+), A") {
                const uint8_t opcode = 0x22U;
                registers->setHL(address);
                testBasicLoad(
                  bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(address); });
                REQUIRE(registers->getHL() == (address + 1));
            }
            SECTION("LD (HL-), A") {
                const uint8_t opcode = 0x32U;
                registers->setHL(address);
                testBasicLoad(
                  bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(address); });
                REQUIRE(registers->getHL() == (address - 1));
            }
            SECTION("LD (HL), A") {
                const uint8_t opcode = 0x77U;
                registers->setHL(address);
                testBasicLoad(
                  bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
        }
        SECTION("Load from non-A register") {
            const int requiredClocks = 8;
            registers->setHL(address);
            SECTION("LD (HL), B") {
                registers->setB(expected);
                testBasicLoad(
                  bus, 0x70U, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (HL), C") {
                registers->setC(expected);
                testBasicLoad(
                  bus, 0x71U, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (HL), D") {
                registers->setD(expected);
                testBasicLoad(
                  bus, 0x72U, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (HL), E") {
                registers->setE(expected);
                testBasicLoad(
                  bus, 0x73U, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (HL), H") {
                registers->setH(expected);
                testBasicLoad(
                  bus, 0x74U, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (HL), L") {
                registers->setB(expected);
                testBasicLoad(
                  bus, 0x75U, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
        }
        SECTION("LD (HL), d8") {
            const int requiredClocks = 12;
            const uint8_t opcode = 0x36U;
            registers->setHL(address);
            bus.write(0x01U, expected);
            testBasicLoad(bus, opcode, requiredClocks, expected, [&bus, address]() {
                return bus.read(address);
            });
        }
        SECTION("Load to A") {
            const int requiredClocks = 8;
            bus.write(address, expected);
            SECTION("LD A, (BC)") {
                const uint8_t opcode = 0x0AU;
                registers->setBC(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() {
                    return registers->getA();
                });
            }
            SECTION("LD A, (DE)") {
                const uint8_t opcode = 0x1AU;
                registers->setDE(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() {
                    return registers->getA();
                });
            }
            SECTION("LD A, (HL+)") {
                const uint8_t opcode = 0x2AU;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() {
                    return registers->getA();
                });
                REQUIRE(registers->getHL() == (address + 1));
            }
            SECTION("LD A, (HL-)") {
                const uint8_t opcode = 0x3AU;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() {
                    return registers->getA();
                });
                REQUIRE(registers->getHL() == (address - 1));
            }
        }
        SECTION("Load to non-A register") {
            const int requiredClocks = 8;
            bus.write(address, expected);
            SECTION("LD A, (HL)") {
                const uint8_t opcode = 0x7EU;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() {
                    return registers->getA();
                });
            }
            SECTION("LD B, (HL)") {
                const uint8_t opcode = 0x46U;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() {
                    return registers->getB();
                });
            }
            SECTION("LD C, (HL)") {
                const uint8_t opcode = 0x4EU;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() {
                    return registers->getC();
                });
            }
            SECTION("LD D, (HL)") {
                const uint8_t opcode = 0x56U;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() {
                    return registers->getD();
                });
            }
            SECTION("LD E, (HL)") {
                const uint8_t opcode = 0x5EU;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() {
                    return registers->getE();
                });
            }
            SECTION("LD H, (HL)") {
                const uint8_t opcode = 0x66U;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() {
                    return registers->getH();
                });
            }
            SECTION("LD L, (HL)") {
                const uint8_t opcode = 0x6EU;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() {
                    return registers->getL();
                });
            }
        }
    }
    SECTION("Register to register loads") {
        SECTION("LD A, A") { testRegisterToRegisterLoad(bus, registers.get(), 0x7FU, 'A', 'A'); }
        SECTION("LD A, B") { testRegisterToRegisterLoad(bus, registers.get(), 0x78U, 'B', 'A'); }
        SECTION("LD A, C") { testRegisterToRegisterLoad(bus, registers.get(), 0x79U, 'C', 'A'); }
        SECTION("LD A, D") { testRegisterToRegisterLoad(bus, registers.get(), 0x7AU, 'D', 'A'); }
        SECTION("LD A, E") { testRegisterToRegisterLoad(bus, registers.get(), 0x7BU, 'E', 'A'); }
        SECTION("LD A, H") { testRegisterToRegisterLoad(bus, registers.get(), 0x7CU, 'H', 'A'); }
        SECTION("LD A, L") { testRegisterToRegisterLoad(bus, registers.get(), 0x7DU, 'L', 'A'); }

        SECTION("LD L, A") { testRegisterToRegisterLoad(bus, registers.get(), 0x6FU, 'A', 'L'); }
        SECTION("LD L, B") { testRegisterToRegisterLoad(bus, registers.get(), 0x68U, 'B', 'L'); }
        SECTION("LD L, C") { testRegisterToRegisterLoad(bus, registers.get(), 0x69U, 'C', 'L'); }
        SECTION("LD L, D") { testRegisterToRegisterLoad(bus, registers.get(), 0x6AU, 'D', 'L'); }
        SECTION("LD L, E") { testRegisterToRegisterLoad(bus, registers.get(), 0x6BU, 'E', 'L'); }
        SECTION("LD L, H") { testRegisterToRegisterLoad(bus, registers.get(), 0x6CU, 'H', 'L'); }
        SECTION("LD L, L") { testRegisterToRegisterLoad(bus, registers.get(), 0x6DU, 'L', 'L'); }

        SECTION("LD E, A") { testRegisterToRegisterLoad(bus, registers.get(), 0x5FU, 'A', 'E'); }
        SECTION("LD E, B") { testRegisterToRegisterLoad(bus, registers.get(), 0x58U, 'B', 'E'); }
        SECTION("LD E, C") { testRegisterToRegisterLoad(bus, registers.get(), 0x59U, 'C', 'E'); }
        SECTION("LD E, D") { testRegisterToRegisterLoad(bus, registers.get(), 0x5AU, 'D', 'E'); }
        SECTION("LD E, E") { testRegisterToRegisterLoad(bus, registers.get(), 0x5BU, 'E', 'E'); }
        SECTION("LD E, H") { testRegisterToRegisterLoad(bus, registers.get(), 0x5CU, 'H', 'E'); }
        SECTION("LD E, L") { testRegisterToRegisterLoad(bus, registers.get(), 0x5DU, 'L', 'E'); }

        SECTION("LD C, A") { testRegisterToRegisterLoad(bus, registers.get(), 0x4FU, 'A', 'C'); }
        SECTION("LD C, B") { testRegisterToRegisterLoad(bus, registers.get(), 0x48U, 'B', 'C'); }
        SECTION("LD C, C") { testRegisterToRegisterLoad(bus, registers.get(), 0x49U, 'C', 'C'); }
        SECTION("LD C, D") { testRegisterToRegisterLoad(bus, registers.get(), 0x4AU, 'D', 'C'); }
        SECTION("LD C, E") { testRegisterToRegisterLoad(bus, registers.get(), 0x4BU, 'E', 'C'); }
        SECTION("LD C, H") { testRegisterToRegisterLoad(bus, registers.get(), 0x4CU, 'H', 'C'); }
        SECTION("LD C, L") { testRegisterToRegisterLoad(bus, registers.get(), 0x4DU, 'L', 'C'); }

        SECTION("LD B, A") { testRegisterToRegisterLoad(bus, registers.get(), 0x47U, 'A', 'B'); }
        SECTION("LD B, B") { testRegisterToRegisterLoad(bus, registers.get(), 0x40U, 'B', 'B'); }
        SECTION("LD B, C") { testRegisterToRegisterLoad(bus, registers.get(), 0x41U, 'C', 'B'); }
        SECTION("LD B, D") { testRegisterToRegisterLoad(bus, registers.get(), 0x42U, 'D', 'B'); }
        SECTION("LD B, E") { testRegisterToRegisterLoad(bus, registers.get(), 0x43U, 'E', 'B'); }
        SECTION("LD B, H") { testRegisterToRegisterLoad(bus, registers.get(), 0x44U, 'H', 'B'); }
        SECTION("LD B, L") { testRegisterToRegisterLoad(bus, registers.get(), 0x45U, 'L', 'B'); }

        SECTION("LD D, A") { testRegisterToRegisterLoad(bus, registers.get(), 0x57U, 'A', 'D'); }
        SECTION("LD D, B") { testRegisterToRegisterLoad(bus, registers.get(), 0x50U, 'B', 'D'); }
        SECTION("LD D, C") { testRegisterToRegisterLoad(bus, registers.get(), 0x51U, 'C', 'D'); }
        SECTION("LD D, D") { testRegisterToRegisterLoad(bus, registers.get(), 0x52U, 'D', 'D'); }
        SECTION("LD D, E") { testRegisterToRegisterLoad(bus, registers.get(), 0x53U, 'E', 'D'); }
        SECTION("LD D, H") { testRegisterToRegisterLoad(bus, registers.get(), 0x54U, 'H', 'D'); }
        SECTION("LD D, L") { testRegisterToRegisterLoad(bus, registers.get(), 0x55U, 'L', 'D'); }

        SECTION("LD H, A") { testRegisterToRegisterLoad(bus, registers.get(), 0x67U, 'A', 'H'); }
        SECTION("LD H, B") { testRegisterToRegisterLoad(bus, registers.get(), 0x60U, 'B', 'H'); }
        SECTION("LD H, C") { testRegisterToRegisterLoad(bus, registers.get(), 0x61U, 'C', 'H'); }
        SECTION("LD H, D") { testRegisterToRegisterLoad(bus, registers.get(), 0x62U, 'D', 'H'); }
        SECTION("LD H, E") { testRegisterToRegisterLoad(bus, registers.get(), 0x63U, 'E', 'H'); }
        SECTION("LD H, H") { testRegisterToRegisterLoad(bus, registers.get(), 0x64U, 'H', 'H'); }
        SECTION("LD H, L") { testRegisterToRegisterLoad(bus, registers.get(), 0x65U, 'L', 'H'); }
    }
    SECTION("Indirect one bit loads") {
        const uint16_t prefix = 0xFF00U;
        const uint8_t addr = 0x52U;
        SECTION("LD (a8), A") {
            const int requiredClocks = 12;
            const uint8_t opcode = 0xE0U;
            registers->setA(expected);
            bus.write(0x01U, addr);
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(prefix + addr); });
        }
        SECTION("LD A, (a8)") {
            const int requiredClocks = 12;
            const uint8_t opcode = 0xF0U;
            bus.write(prefix + addr, expected);
            bus.write(0x01, addr);
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [registers]() { return registers->getA(); });
        }
        SECTION("LD (C), A") {
            const int requiredClocks = 8;
            const uint8_t opcode = 0xE2U;
            registers->setA(expected);
            registers->setC(addr);
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(prefix + addr); });
        }
        SECTION("LD A, (C)") {
            const int requiredClocks = 8;
            const uint8_t opcode = 0xF2U;
            bus.write(prefix + addr, expected);
            registers->setC(addr);
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [registers]() { return registers->getA(); });
        }
    }
    SECTION("Indirect two bit loads") {
        const uint16_t addr = 0x1234U;
        const uint8_t highByte = 0x12U;
        const uint8_t lowByte = 0x34U;

        bus.write(0x01, highByte);
        bus.write(0x02, lowByte);

        SECTION("LD (a16), A") {
            const int requiredClocks = 16;
            const uint8_t opcode = 0xEAU;
            registers->setA(expected);
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(addr); });
        }
        SECTION("LD A, (a16)") {
            const int requiredClocks = 16;
            const uint8_t opcode = 0xFAU;
            bus.write(addr, expected);
            testBasicLoad(
              bus, opcode, requiredClocks, expected, [registers]() { return registers->getA(); });
        }
    }
}