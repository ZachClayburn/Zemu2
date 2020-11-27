#include "Push.h"

#include <tuple>
#include "CPURegisters.h"
#include "IBus.h"

Push::Push(IBus* busIn, CPURegisters* registersIn, Target targetIn)
  : Operation(LENGTH), bus(busIn), registers(registersIn), target(targetIn) {}

interimValue_t Push::operator()(interimValue_t /*value*/) {
    uint8_t high = 0;
    uint8_t low = 0;

    switch (target) {
    case Push::BC:
        std::tie(high, low) = std::make_tuple(registers->getB(), registers->getC());
        break;
    case Push::DE:
        std::tie(high, low) = std::make_tuple(registers->getD(), registers->getE());
        break;
    case Push::HL:
        std::tie(high, low) = std::make_tuple(registers->getH(), registers->getL());
        break;
    case Push::AF:
        std::tie(high, low) = std::make_tuple(registers->getA(), registers->getF());
        break;
    }

    bus->write(registers->getSP(), high);
    registers->decSP();
    bus->write(registers->getSP(), low);
    registers->decSP();

    return interimValue_t();
}
