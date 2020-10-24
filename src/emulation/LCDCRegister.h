#ifndef ZEMU2_LCDCREGISTER_H
#define ZEMU2_LCDCREGISTER_H


#include "BasicRegister.h"

class LCDCRegister : public BasicRegister
{
  public:
    explicit LCDCRegister(uint16_t addr);

    bool displayEnable();
    uint16_t windowTileMap();
    bool windowEnable();

    /**
     * Get the current start address for the background/window tile data
     * @return The start address for tile data: 0x8000 if using unsigned tile numbers
     *         or 0x9000 if using signed tile numbers.
     */
    uint16_t bgWindowTileData();
    uint16_t bgTileMap();
    uint8_t objSize();
    bool objEnable();
    bool bgDisplay();
    const static constexpr uint16_t TILE_DATA_UNSIGNED_START_ADDR = 0x8000U;// 0x8000 - 0x8FFF
    const static constexpr uint16_t TILE_DATA_SIGNED_START_ADDR = 0x9000U;// 0x8800 - 0x97FF
};


#endif// ZEMU2_LCDCREGISTER_H
