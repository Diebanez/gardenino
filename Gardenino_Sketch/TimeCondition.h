#pragma once

#include "Clock.h"
#include "Condition.h"
#include "Range.h"


class TimeCondition : public Condition
{
public:
	TimeCondition(Clock* globalClock, Range<DateTime> timeRange);
	virtual bool Evaluate() override;

private:
	Clock* GlobalClock;
	Range<DateTime> TimeRange;
};