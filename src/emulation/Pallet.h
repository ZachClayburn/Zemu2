#ifndef ZEMU2_PALLET_H
#define ZEMU2_PALLET_H

#include <array>

#include "ReadWriteDevice.h"

class Pallet : public ReadWriteDevice
{
  public:
    enum Shade : uint8_t {
        WHITE = 0b00,
        LIGHT_GRAY = 0b01,
        DARK_GRAY = 0b10,
        BLACK = 0b11,
    };
    explicit Pallet(uint16_t addr);

    uint8_t read(uint16_t addr) override;
    void write(uint16_t addr, uint8_t val) override;
    bool accepts(uint16_t addr) override;
    
    [[nodiscard]] Shade operator[](uint8_t n);
  private:
    uint16_t palletAddr;
    std::array<Shade, 4> shades;
};


#endif//ZEMU2_PALLET_H
