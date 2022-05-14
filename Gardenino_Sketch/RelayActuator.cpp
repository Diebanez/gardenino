#include "RelayActuator.h"

#include "Debug.h"


RelayActuator::RelayActuator(const uint8_t& actuatorPin, Clock* clock)
	: ActuatorPin(actuatorPin), LastCondition(false), GlobalClock(clock)
{
}

void RelayActuator::Init()
{
	pinMode(ActuatorPin, OUTPUT);
}

void RelayActuator::AddCondition(Condition* condition)
{
	ActuationConditions.AddElement(condition);
}

void RelayActuator::Update()
{
	bool newCondition = CheckAllConditions();

	if (newCondition == LastCondition)
	{
		return;
	}

	if (newCondition)
	{
		LastStartActivationTime = GlobalClock->GetNow();
	}
	else
	{
		LastEndActivationTime = GlobalClock->GetNow();
	}

	digitalWrite(ActuatorPin, !newCondition);
	LastCondition = newCondition;
}

bool RelayActuator::CheckAllConditions()
{
	bool result = true;

	for (int i = 0; i < ActuationConditions.GetElementsCount(); i++)
	{
		result = result && ActuationConditions.GetElement(i)->Evaluate();
		if (!result)
		{
			break;
		}
	}

	return result;
}

bool RelayActuator::IsActive() const
{
	return LastCondition;
}