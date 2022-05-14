#include "MinOffsetTimeCondition.h"

MinOffsetTimeCondition::MinOffsetTimeCondition(Clock* globalClock, RelayActuator* actuator, float minTime)
	: GlobalClock(globalClock), TargetActuator(actuator), MinOffsetTime(minTime)
{
}

bool MinOffsetTimeCondition::Evaluate()
{
	if (TargetActuator->IsActive())
	{
		return true;
	}

	return GlobalClock->GetNow().secondstime() - TargetActuator->LastEndActivationTime.secondstime() > MinOffsetTime;
}