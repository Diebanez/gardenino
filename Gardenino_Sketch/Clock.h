#pragma once

#include <Wire.h>
#include <RTClib.h>

class Clock
{
public:
    bool Init();
    String GetDate();
    String GetTime();
    DateTime GetNow();

private:
    RTC_DS3231 ClockModule;
};