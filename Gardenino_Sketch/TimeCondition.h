#pragma once

#include "Condition.h"
#include "Clock.h"
#include "Range.h"

class TimeCondition : public Condition
{
public:
    TimeCondition(Clock *globalClock, Range<DateTime> timeRange);
    virtual bool Evaluate() override;

private:
    Clock *GlobalClock;
    Range<DateTime> TimeRange;
};