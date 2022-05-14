#pragma once

#include "Clock.h"
#include "Condition.h"
#include "RelayActuator.h"

class MaxActivationTimeCondition : public Condition
{
public:
	MaxActivationTimeCondition(Clock* globalClock, RelayActuator* actuator, float maxTime);
	virtual bool Evaluate() override;

private:
	Clock* GlobalClock;
	RelayActuator* TargetActuator;
	float MaxActiveTime;
};