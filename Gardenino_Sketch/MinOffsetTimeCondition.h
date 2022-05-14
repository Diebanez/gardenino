#pragma once

#include "Clock.h"
#include "Condition.h"
#include "RelayActuator.h"

class MinOffsetTimeCondition : public Condition
{
public:
	MinOffsetTimeCondition(Clock* globalClock, RelayActuator* actuator, float minTime);
	virtual bool Evaluate() override;

private:
	Clock* GlobalClock;
	RelayActuator* TargetActuator;
	float MinOffsetTime;
};