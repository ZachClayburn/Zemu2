//
// Created by zach on 5/2/20.
//

#ifndef ZEMU2_READWRITEDEVICE_H
#define ZEMU2_READWRITEDEVICE_H

#include <cstdint>

class ReadWriteDevice
{
  public:
    virtual ~ReadWriteDevice() = default;
    
    virtual uint8_t read(uint16_t addr) = 0;
    virtual void write(uint16_t addr, uint8_t val) = 0;
    virtual bool accepts(uint16_t addr) = 0;
    
    static const uint8_t BAD_READ{ 0xFFU };
};


#endif//ZEMU2_READWRITEDEVICE_H
