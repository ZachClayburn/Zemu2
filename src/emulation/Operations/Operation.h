#ifndef ZEMU2_OPERATION_H
#define ZEMU2_OPERATION_H


#include <cstdint>
#include <variant>

using interimValue_t = std::variant<std::monostate, uint8_t, uint16_t>;

class IBus;
class CPURegisters;

class Operation
{
  public:
    explicit Operation(uint8_t lengthIn);
    virtual ~Operation() = default;

    [[nodiscard]] uint8_t getLength() const;

    virtual interimValue_t operator()(interimValue_t) = 0;

  private:
    uint8_t length;
};


#endif// ZEMU2_OPERATION_H
