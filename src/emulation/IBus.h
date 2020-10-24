#ifndef ZEMU2_IBUS_H
#define ZEMU2_IBUS_H

#include <cstdint>

class IBus
{
  public:
    virtual ~IBus() = default;

    virtual void clock() = 0;

    virtual uint8_t read(uint16_t) = 0;
    virtual void write(uint16_t addr, uint8_t val) = 0;
};


#endif// ZEMU2_IBUS_H
