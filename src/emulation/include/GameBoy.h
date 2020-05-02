//
// Created by zach on 5/2/20.
//

#ifndef ZEMU2_GAMEBOY_H
#define ZEMU2_GAMEBOY_H

#include <array>
#include <memory>

class ReadWriteDevice;
class BootRom;
class IRamBank;

class GameBoy
{
  public:
    GameBoy();
    ~GameBoy() = default;
  private:
    
    static const size_t NUM_DEVICES = 4;
    std::array<std::shared_ptr<ReadWriteDevice>, NUM_DEVICES> devices;
    
    std::shared_ptr<BootRom> bootRom;
    std::shared_ptr<IRamBank> wRam;
    std::shared_ptr<IRamBank> hRam;
    
};


#endif//ZEMU2_GAMEBOY_H
