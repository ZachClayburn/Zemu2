#ifndef ZEMU2_MOCKBUS_H
#define ZEMU2_MOCKBUS_H

#include <array>
#include <limits>
#include "IBus.h"
#include "CPU.h"

class MockBus : IBus
{
  public:
    MockBus();
    ~MockBus() override = default;
    void clock() override;
    uint8_t read(uint16_t addr) override;
    void write(uint16_t addr, uint8_t val) override;

    CPU& getCpu();

  private:
    CPU cpu;
    std::array<uint8_t, std::numeric_limits<uint16_t>::max()> ram;
};


#endif// ZEMU2_MOCKBUS_H
