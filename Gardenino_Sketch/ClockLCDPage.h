#pragma once

#include "LCDPage.h"
#include "Clock.h"

class ClockLCDPage : public LCDPage
{
public:
    ClockLCDPage(Clock *targetClock);
    virtual void PrintPage(LiquidCrystal_I2C &lcd) override;
    virtual void Update(LiquidCrystal_I2C &lcd) override;

private:
    Clock *TargetClock;
};