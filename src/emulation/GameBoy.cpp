#include "GameBoy.h"

#include "Bus.h"

GameBoy::GameBoy(const std::shared_ptr<std::array<Pixel, PIXEL_COUNT>>& screenBuffer,
  void (*screenCallback)())
  : bus(std::make_unique<Bus>(screenBuffer, screenCallback)) {}

GameBoy::~GameBoy() = default;

void GameBoy::clock() { bus->clock(); }
