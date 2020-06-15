#ifndef ZEMU2_OPERATION_H
#define ZEMU2_OPERATION_H


#include <cstdint>
#include <variant>

class Operation
{
  public:
    explicit Operation(uint8_t lengthIn);
    virtual ~Operation() = default;
    
    [[nodiscard]] uint8_t getLength() const;

    virtual std::variant<uint8_t, uint16_t> operator()(std::variant<uint8_t, uint16_t>) = 0;

  private:
    uint8_t length;
};


#endif//ZEMU2_OPERATION_H
