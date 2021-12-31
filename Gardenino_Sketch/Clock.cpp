#include "Clock.h"

bool Clock::Init()
{
    if (!ClockModule.begin())
    {
        return false;
    }

    if (ClockModule.lostPower())
    {
        ClockModule.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    return true;
}

String Clock::GetDate()
{
    DateTime now = GetNow();

    return String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());
}

String Clock::GetTime()
{

    DateTime now = GetNow();
    return String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
}

DateTime Clock::GetNow()
{
    DateTime now = ClockModule.now();
    return now;
}
