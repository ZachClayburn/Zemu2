#ifndef ZEMU2_CPUREGISTERS_H
#define ZEMU2_CPUREGISTERS_H

#include <cstdint>


class CPURegisters
{
  public:
    [[nodiscard]] uint8_t getA() const;
    void setA(uint8_t value);

    [[nodiscard]] uint8_t getF() const;
    void setF(uint8_t value);

    [[nodiscard]] uint8_t getB() const;
    void setB(uint8_t value);

    [[nodiscard]] uint8_t getC() const;
    void setC(uint8_t value);

    [[nodiscard]] uint8_t getD() const;
    void setD(uint8_t value);

    [[nodiscard]] uint8_t getE() const;
    void setE(uint8_t value);

    [[nodiscard]] uint8_t getH() const;
    void setH(uint8_t value);

    [[nodiscard]] uint8_t getL() const;
    void setL(uint8_t value);

    [[nodiscard]] uint16_t getAF() const;
    void setAF(uint16_t value);

    [[nodiscard]] uint16_t getBC() const;
    void setBC(uint16_t value);

    [[nodiscard]] uint16_t getDE() const;
    void setDE(uint16_t value);

    [[nodiscard]] uint16_t getHL() const;
    void setHL(uint16_t value);
    void indHL();
    void decHL();

    [[nodiscard]] uint16_t getSP() const;
    void setSP(uint16_t value);
    void incSP();
    void decSP();

    [[nodiscard]] uint16_t getPC() const;
    void setPC(uint16_t value);
    void incPC();

    [[nodiscard]] bool checkZFlag() const;
    void setZFlag(bool flag);

    [[nodiscard]] bool checkNFlag() const;
    void setNFlag(bool flag);

    [[nodiscard]] bool checkHFlag() const;
    void setHFlag(bool flag);

    [[nodiscard]] bool checkCFlag() const;
    void setCFlag(bool flag);

  private:
    uint8_t A{ 0 };
    uint8_t F{ 0 };
    uint8_t B{ 0 };
    uint8_t C{ 0 };
    uint8_t D{ 0 };
    uint8_t E{ 0 };
    uint8_t H{ 0 };
    uint8_t L{ 0 };
    uint16_t SP{ 0 };
    uint16_t PC{ 0 };
};


#endif// ZEMU2_CPUREGISTERS_H
