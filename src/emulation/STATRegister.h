#ifndef ZEMU2_STATREGISTER_H
#define ZEMU2_STATREGISTER_H


#include "BasicRegister.h"

class STATRegister : public BasicRegister
{
  public:
    enum MODE : uint8_t {
        H_BLANK = 0,
        V_BLANK = 1,
        OAM_SEARCH = 2,
        OAM_TRANSFER = 3,
    };

    explicit STATRegister(uint16_t addr) : BasicRegister(addr) {}
    ~STATRegister() override = default;

    bool coincidenceInterruptEnabled();
    bool oamInterruptEnabled();
    bool vBlankInterruptEnabled();
    bool hBlankInterruptEnabled();
    [[nodiscard]] bool coincidenceFlag() const;
    MODE modeFlag();

    void setCoincidence(bool coincidence);
    void setMode(MODE mode);

    uint8_t read(uint16_t addr) override;

  private:
    bool coincidence = false;
    MODE mode{ OAM_SEARCH };
};


#endif// ZEMU2_STATREGISTER_H
