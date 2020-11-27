#include "Pop.h"

#include "CPURegisters.h"
#include "IBus.h"
#include "bitUtils.h"

Pop::Pop(IBus* busIn, CPURegisters* registersIn, Pop::Target targetIn)
  : Operation(LENGTH), bus(busIn), registers(registersIn), target(targetIn) {}

interimValue_t Pop::operator()(interimValue_t /*value*/) {
    const auto low = bus->read(registers->getSP());
    registers->incSP();
    const auto high = bus->read(registers->getSP());
    registers->incSP();
    const auto merged = mergeBytes(high, low);

    switch (target) {
    case BC:
        registers->setBC(merged);
        break;
    case DE:
        registers->setDE(merged);
        break;
    case HL:
        registers->setHL(merged);
        break;
    case AF:
        registers->setAF(merged);
        break;
    }
    return interimValue_t();
}
