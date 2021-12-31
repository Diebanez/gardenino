#include "TimeCondition.h"

TimeCondition::TimeCondition(Clock *globalClock, Range<DateTime> timeRange)
    : GlobalClock(globalClock), TimeRange(DateTime(2000, 1, 1, timeRange.Start.hour(), timeRange.Start.minute(), timeRange.Start.second()), DateTime(2000, 1, 1, timeRange.End.hour(), timeRange.End.minute(), timeRange.End.second()))
{
}
bool TimeCondition::Evaluate()
{
    DateTime now = GlobalClock->GetNow();
    DateTime nowTime(2000, 1, 1, now.hour(), now.minute(), now.second());

    return nowTime >= TimeRange.Start && nowTime <= TimeRange.End;
}