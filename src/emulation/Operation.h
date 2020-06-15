#ifndef ZEMU2_OPERATION_H
#define ZEMU2_OPERATION_H


#include <cstdint>

class Operation
{
  public:
    explicit Operation(uint8_t lengthIn);
    virtual ~Operation() = default;
    
    [[nodiscard]] uint8_t getLength() const;

    virtual void operator()() = 0;

  private:
    uint8_t length;
};


#endif//ZEMU2_OPERATION_H
