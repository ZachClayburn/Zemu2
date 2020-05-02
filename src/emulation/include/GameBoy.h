//
// Created by zach on 5/2/20.
//

#ifndef ZEMU2_GAMEBOY_H
#define ZEMU2_GAMEBOY_H

#include <array>
#include <memory>

class ReadWriteDevice;
class BootRom;

class GameBoy
{
  public:
    GameBoy();
    ~GameBoy() = default;
  private:
    
    static const size_t NUM_DEVICES = 1;
    std::array<std::shared_ptr<ReadWriteDevice>, NUM_DEVICES> devices;
    
    std::shared_ptr<BootRom> bootRom;
    
};


#endif//ZEMU2_GAMEBOY_H
