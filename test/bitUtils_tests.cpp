#include <catch2/catch.hpp>

#include "bitUtils.h"

TEST_CASE("Test bit utils") {
    SECTION("Test split bytes") {
        const uint8_t highByteExpected = 0xABU;
        const uint8_t lowByteExpected = 0xCDU;
        const uint16_t merged = 0xABCDU;

        auto [highByte, lowByte] = splitBytes(merged);
        REQUIRE(highByteExpected == highByte);
        REQUIRE(lowByteExpected == lowByte);
    }
    SECTION("Test merge bytes") {
        const uint8_t lowByte = 0xCDU;
        const uint8_t highByte = 0xABU;
        const uint16_t expected = 0xABCDU;
        uint16_t merged = mergeBytes(highByte, lowByte);
        REQUIRE(merged == expected);
    }
}