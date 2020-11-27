#include "CPURegisters.h"

#include "bitUtils.h"

uint8_t CPURegisters::getA() const { return A; }

void CPURegisters::setA(uint8_t value) { A = value; }

uint8_t CPURegisters::getF() const { return F; }

void CPURegisters::setF(uint8_t value) { F = value; }

uint8_t CPURegisters::getB() const { return B; }

void CPURegisters::setB(uint8_t value) { B = value; }

uint8_t CPURegisters::getC() const { return C; }

void CPURegisters::setC(uint8_t value) { C = value; }

uint8_t CPURegisters::getD() const { return D; }

void CPURegisters::setD(uint8_t value) { D = value; }

uint8_t CPURegisters::getE() const { return E; }

void CPURegisters::setE(uint8_t value) { E = value; }

uint8_t CPURegisters::getH() const { return H; }

void CPURegisters::setH(uint8_t value) { H = value; }

uint8_t CPURegisters::getL() const { return L; }

void CPURegisters::setL(uint8_t value) { L = value; }

uint16_t CPURegisters::getAF() const { return mergeBytes(A, F); }

void CPURegisters::setAF(uint16_t value) { std::tie(A, F) = splitBytes(value); }

uint16_t CPURegisters::getBC() const { return mergeBytes(B, C); }

void CPURegisters::setBC(uint16_t value) { std::tie(B, C) = splitBytes(value); }

uint16_t CPURegisters::getDE() const { return mergeBytes(D, E); }

void CPURegisters::setDE(uint16_t value) { std::tie(D, E) = splitBytes(value); }

uint16_t CPURegisters::getHL() const { return mergeBytes(H, L); }

void CPURegisters::setHL(uint16_t value) { std::tie(H, L) = splitBytes(value); }

void CPURegisters::indHL() {
    auto value = mergeBytes(H, L);
    value++;
    setHL(value);
}

void CPURegisters::decHL() {
    auto value = mergeBytes(H, L);
    value--;
    setHL(value);
}

uint16_t CPURegisters::getSP() const { return SP; }

void CPURegisters::setSP(uint16_t value) { SP = value; }
void CPURegisters::incSP() { ++SP; }
void CPURegisters::decSP() { --SP; }

uint16_t CPURegisters::getPC() const { return PC; }

void CPURegisters::setPC(uint16_t value) { PC = value; }

void CPURegisters::incPC() { ++PC; }

constexpr const static uint8_t Z_BIT{ 7 };
bool CPURegisters::checkZFlag() const { return readBit(F, Z_BIT); }
void CPURegisters::setZFlag(bool flag) { F = setBit(F, Z_BIT, flag); }

constexpr const static uint8_t N_BIT{ 6 };
bool CPURegisters::checkNFlag() const { return readBit(F, N_BIT); }
void CPURegisters::setNFlag(bool flag) { F = setBit(F, N_BIT, flag); }

constexpr const static uint8_t H_BIT{ 5 };
bool CPURegisters::checkHFlag() const { return readBit(F, H_BIT); }
void CPURegisters::setHFlag(bool flag) { F = setBit(F, H_BIT, flag); }

constexpr const static uint8_t C_BIT{ 4 };
bool CPURegisters::checkCFlag() const { return readBit(F, C_BIT); }
void CPURegisters::setCFlag(bool flag) { F = setBit(F, C_BIT, flag); }
