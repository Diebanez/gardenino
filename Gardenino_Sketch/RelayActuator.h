#pragma once

#include "Clock.h"
#include "Collection.h"
#include "Condition.h"

#include <Arduino.h>
#include <stdint.h>


class RelayActuator
{
public:
	RelayActuator(const uint8_t& actuatorPin, Clock* clock);
	void Init();
	void AddCondition(Condition* condition);
	void Update();
	bool IsActive() const;

	DateTime LastStartActivationTime;
	DateTime LastEndActivationTime;

private:
	bool CheckAllConditions();

	uint8_t ActuatorPin;
	Collection<Condition> ActuationConditions;
	bool LastCondition;
	Clock* GlobalClock;
};