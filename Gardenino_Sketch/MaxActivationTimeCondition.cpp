#include "MaxActivationTimeCondition.h"

MaxActivationTimeCondition::MaxActivationTimeCondition(Clock* globalClock, RelayActuator* actuator, float maxTime)
	: GlobalClock(globalClock), TargetActuator(actuator), MaxActiveTime(maxTime)
{
}

bool MaxActivationTimeCondition::Evaluate()
{
	if (!TargetActuator->IsActive())
	{
		return true;
	}
	return GlobalClock->GetNow().secondstime() - TargetActuator->LastStartActivationTime.secondstime() < MaxActiveTime;
}