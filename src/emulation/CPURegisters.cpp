#include "CPURegisters.h"

#include "bitUtils.h"

uint8_t CPURegisters::getA() const {
    return A;
}

void CPURegisters::setA(uint8_t value) {
    A = value;
}

uint8_t CPURegisters::getF() const {
    return F;
}

void CPURegisters::setF(uint8_t value) {
    F = value;
}

uint8_t CPURegisters::getB() const {
    return B;
}

void CPURegisters::setB(uint8_t value) {
    B = value;
}

uint8_t CPURegisters::getC() const {
    return C;
}

void CPURegisters::setC(uint8_t value) {
    C = value;
}

uint8_t CPURegisters::getD() const {
    return D;
}

void CPURegisters::setD(uint8_t value) {
    D = value;
}

uint8_t CPURegisters::getE() const {
    return E;
}

void CPURegisters::setE(uint8_t value) {
    E = value;
}

uint8_t CPURegisters::getH() const {
    return H;
}

void CPURegisters::setH(uint8_t value) {
    H = value;
}

uint8_t CPURegisters::getL() const {
    return L;
}

void CPURegisters::setL(uint8_t value) {
    L = value;
}

uint16_t CPURegisters::getAF() const {
    return mergeBytes(A, F);
}

void CPURegisters::setAF(uint16_t value) {
    splitBytes(value, A, F);
}

uint16_t CPURegisters::getBC() const {
    return mergeBytes(B, C);
}

void CPURegisters::setBC(uint16_t value) {
    splitBytes(value, B, C);
}

uint16_t CPURegisters::getDE() const {
    return mergeBytes(D, E);
}

void CPURegisters::setDE(uint16_t value) {
    splitBytes(value, D, E);
}

uint16_t CPURegisters::getHL() const {
    return mergeBytes(H, L);
}

void CPURegisters::setHL(uint16_t value) {
    splitBytes(value, H, L);
}

uint16_t CPURegisters::getSP() const {
    return SP;
}

void CPURegisters::setSP(uint16_t value) {
    PC = value;
}

uint16_t CPURegisters::getPC() const {
    return SP;
}

void CPURegisters::setPC(uint16_t value) {
    SP = value;
}
