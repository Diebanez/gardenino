#include "ClockLCDPage.h"

ClockLCDPage::ClockLCDPage(Clock *targetClock)
{
    TargetClock = targetClock;
}

void ClockLCDPage::PrintPage(LiquidCrystal_I2C &lcd)
{
    lcd.clear();
    Update(lcd);
}

void ClockLCDPage::Update(LiquidCrystal_I2C &lcd)
{
    lcd.setCursor(0, 0);
    lcd.print("Date " + TargetClock->GetDate());
    lcd.setCursor(0, 1);
    lcd.print("Time " + TargetClock->GetTime());
}