#include "DirectLoadAndAddAsSigned.h"

#include "Bus.h"
#include "CPURegisters.h"
#include "bitUtils.h"

DirectLoadAndAddAsSigned::DirectLoadAndAddAsSigned(IBus* busIn, CPURegisters* registersIn)
  : Operation(LENGTH), bus(busIn), registers(registersIn) {}

interimValue_t DirectLoadAndAddAsSigned::operator()(interimValue_t value) {
    auto parameter = bus->read(registers->getPC());
    registers->incPC();

    registers->setZFlag(false);
    registers->setNFlag(false);
    struct Visitor
    {
        CPURegisters* registers;
        uint8_t parameter;

        interimValue_t operator()(uint8_t val) const {
            registers->setHFlag(testHalfCarry(parameter, val));
            registers->setCFlag(testCarry(parameter, val));
            return static_cast<uint8_t>(parameter + val);
        }
        interimValue_t operator()(uint16_t val) const {
            registers->setHFlag(testHalfCarry(parameter, static_cast<uint8_t>(val)));
            registers->setCFlag(testCarry(parameter, static_cast<uint8_t>(val)));
            return static_cast<uint16_t>(parameter + val);
        }
        interimValue_t operator()(std::monostate /*val*/) const {
            registers->setHFlag(false);
            registers->setCFlag(false);
            return parameter;
        }
    };

    return std::visit(Visitor{registers, parameter}, value);
}
