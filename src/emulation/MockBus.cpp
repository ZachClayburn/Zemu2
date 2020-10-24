#include "MockBus.h"

#include <algorithm>

MockBus::MockBus() : cpu(this) { std::fill(ram.begin(), ram.end(), 0x00U); }

void MockBus::clock() { cpu.clock(); }

uint8_t MockBus::read(uint16_t addr) { return ram.at(addr); }

void MockBus::write(uint16_t addr, uint8_t val) { ram.at(addr) = val; }
CPU& MockBus::getCpu() { return cpu; }
