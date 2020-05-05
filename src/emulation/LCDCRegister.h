#ifndef ZEMU2_LCDCREGISTER_H
#define ZEMU2_LCDCREGISTER_H


#include "BasicRegister.h"

class LCDCRegister : BasicRegister
{
  public:
    explicit LCDCRegister(uint16_t addr);
    
    bool displayEnable();
    uint16_t windowTileMap();
    bool windowEnable();
    uint16_t bgWindowTileData();
    uint16_t bgTileMap();
    uint8_t objSize();
    bool objEnable();
    bool bgDisplay();
    
};


#endif//ZEMU2_LCDCREGISTER_H
