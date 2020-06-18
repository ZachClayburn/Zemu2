#include <catch2/catch.hpp>

#include <functional>
#include "MockBus.h"
#include "CPURegisters.h"

void testBasicLoad(MockBus &bus,
  uint8_t opcode,
  int requiredClocks,
  uint8_t expected,
  const std::function<uint8_t(void)> &getterFun) {
    bus.write(0x00, opcode);
    for (int i = 0; i < requiredClocks; ++i) {
        bus.clock();
    }
    REQUIRE(getterFun() == expected);
}
TEST_CASE("CPU instruction tests") {
    MockBus bus;
    auto registers = bus.getCpu().getRegisters();
    SECTION("8 bit load from parameter") {
        const uint8_t expected = 0x4A;
        bus.write(0x01, expected);
        const int requiredClocks = 8;
        SECTION("LD A, d8") {
            const uint8_t opcode = 0x3EU;
            testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getA(); });
        }
        SECTION("LD B, d8") {
            const uint8_t opcode = 0x06U;
            testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getB(); });
        }
        SECTION("LD C, d8") {
            const uint8_t opcode = 0x0EU;
            testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getC(); });
        }
        SECTION("LD D, d8") {
            const uint8_t opcode = 0x16U;
            testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getD(); });
        }
        SECTION("LD E, d8") {
            const uint8_t opcode = 0x1EU;
            testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getE(); });
        }
        SECTION("LD H, d8") {
            const uint8_t opcode = 0x26U;
            testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getH(); });
        }
        SECTION("LD L, d8") {
            const uint8_t opcode = 0x2EU;
            testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getL(); });
        }
    }
    SECTION("Indirect load instructions") {
        const uint8_t expected = 0x4AU;
        const uint16_t address = 0x4A4AU;
        SECTION("Load from A") {
            const int requiredClocks = 8;
            registers->setA(expected);
            SECTION("LD (BC), A") {
                const uint8_t opcode = 0x02U;
                registers->setBC(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (DE), A") {
                const uint8_t opcode = 0x12U;
                registers->setDE(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (HL+), A") {
                const uint8_t opcode = 0x22U;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(address); });
                REQUIRE(registers->getHL() == (address + 1));
            }
            SECTION("LD (HL-), A") {
                const uint8_t opcode = 0x32U;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(address); });
                REQUIRE(registers->getHL() == (address - 1));
            }
            SECTION("LD (HL), A") {
                const uint8_t opcode = 0x77U;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
        }
        SECTION("Load from non-A register") {
            const int requiredClocks = 8;
            registers->setHL(address);
            SECTION("LD (HL), B") {
                registers->setB(expected);
                testBasicLoad(bus, 0x70U, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (HL), C") {
                registers->setC(expected);
                testBasicLoad(bus, 0x71U, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (HL), D") {
                registers->setD(expected);
                testBasicLoad(bus, 0x72U, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (HL), E") {
                registers->setE(expected);
                testBasicLoad(bus, 0x73U, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (HL), H") {
                registers->setH(expected);
                testBasicLoad(bus, 0x74U, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
            SECTION("LD (HL), L") {
                registers->setB(expected);
                testBasicLoad(bus, 0x75U, requiredClocks, expected, [&bus]() { return bus.read(address); });
            }
        }
        SECTION("LD (HL), d8") {
            const int requiredClocks = 12;
            const uint8_t opcode = 0x36U;
            registers->setHL(address);
            bus.write(0x01U, expected);
            testBasicLoad(bus, opcode, requiredClocks, expected, [&bus, address]() { return bus.read(address); });
        }
        SECTION("Load to A") {
            const int requiredClocks = 8;
            bus.write(address, expected);
            SECTION("LD A, (BC)") {
                const uint8_t opcode = 0x0AU;
                registers->setBC(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getA(); });
            }
            SECTION("LD A, (DE)") {
                const uint8_t opcode = 0x1AU;
                registers->setDE(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getA(); });
            }
            SECTION("LD A, (HL+)") {
                const uint8_t opcode = 0x2AU;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getA(); });
                REQUIRE(registers->getHL() == (address + 1));
            }
            SECTION("LD A, (HL-)") {
                const uint8_t opcode = 0x3AU;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getA(); });
                REQUIRE(registers->getHL() == (address - 1));
            }
        }
        SECTION("Load to non-A register") {
            const int requiredClocks = 8;
            bus.write(address, expected);
            SECTION("LD A, (HL)") {
                const uint8_t opcode = 0x7EU;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getA(); });
            }
            SECTION("LD B, (HL)") {
                const uint8_t opcode = 0x46U;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getB(); });
            }
            SECTION("LD C, (HL)") {
                const uint8_t opcode = 0x4EU;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getC(); });
            }
            SECTION("LD D, (HL)") {
                const uint8_t opcode = 0x56U;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getD(); });
            }
            SECTION("LD E, (HL)") {
                const uint8_t opcode = 0x5EU;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getE(); });
            }
            SECTION("LD H, (HL)") {
                const uint8_t opcode = 0x66U;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getH(); });
            }
            SECTION("LD L, (HL)") {
                const uint8_t opcode = 0x6EU;
                registers->setHL(address);
                testBasicLoad(bus, opcode, requiredClocks, expected, [registers]() { return registers->getL(); });
            }
        }
    }
}