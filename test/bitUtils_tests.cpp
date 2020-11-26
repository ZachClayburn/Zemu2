#include <catch2/catch.hpp>

#include <array>
#include "bitUtils.h"

TEST_CASE("Bit utils") {
    SECTION("Split bytes") {
        const uint8_t highByteExpected = 0xABU;
        const uint8_t lowByteExpected = 0xCDU;
        const uint16_t merged = 0xABCDU;

        auto [highByte, lowByte] = splitBytes(merged);
        REQUIRE(highByteExpected == highByte);
        REQUIRE(lowByteExpected == lowByte);
    }
    SECTION("Merge bytes") {
        const uint8_t lowByte = 0xCDU;
        const uint8_t highByte = 0xABU;
        const uint16_t expected = 0xABCDU;
        uint16_t merged = mergeBytes(highByte, lowByte);
        REQUIRE(merged == expected);
    }
    SECTION("Read bit") {
        const uint8_t testByte = 0b01000100U;
        const uint8_t bits = 8;
        const std::array<bool, bits> expected{
            false,
            false,
            true,
            false,
            false,
            false,
            true,
            false,
        };

        for (uint8_t i = 0; i < bits; i++) { CHECK(readBit(testByte, i) == expected.at(i)); }
    }
    SECTION("Set bit true") {
        const uint8_t testByte = 0;
        const uint8_t bits = 8;
        const std::array<uint8_t, bits> expected{
            0b00000001U,
            0b00000010U,
            0b00000100U,
            0b00001000U,
            0b00010000U,
            0b00100000U,
            0b01000000U,
            0b10000000U,
        };

        for (uint8_t i = 0; i < bits; i++) { CHECK(setBit(testByte, i, true) == expected.at(i)); }
    }
    SECTION("Set bit false") {
        const uint8_t testByte = 0xFFU;
        const uint8_t bits = 8;
        const std::array<uint8_t, bits> expected{
            0b11111110U,
            0b11111101U,
            0b11111011U,
            0b11110111U,
            0b11101111U,
            0b11011111U,
            0b10111111U,
            0b01111111U,
        };

        for (uint8_t i = 0; i < bits; i++) { CHECK(setBit(testByte, i, false) == expected.at(i)); }
    }
    SECTION("Test carry") {
        SECTION("carry happens") {
            uint8_t byte1 = 128;
            uint8_t byte2 = 128;
            bool expected = true;
            REQUIRE(testCarry(byte1, byte2) == expected);
        }
        SECTION("carry does not happen") {
            uint8_t byte1 = 127;
            uint8_t byte2 = 128;
            bool expected = false;
            REQUIRE(testCarry(byte1, byte2) == expected);
        }
    }
    SECTION("Test half carry") {
        SECTION("carry happens") {
            uint8_t byte1 = 8;
            uint8_t byte2 = 8;
            bool expected = true;
            REQUIRE(testHalfCarry(byte1, byte2) == expected);
        }
        SECTION("carry does not happen") {
            uint8_t byte1 = 7;
            uint8_t byte2 = 8;
            bool expected = false;
            REQUIRE(testHalfCarry(byte1, byte2) == expected);
        }
    }
}