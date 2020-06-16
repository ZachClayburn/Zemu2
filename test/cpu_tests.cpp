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
    SECTION("8 Bit Load from parameter") {
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
}