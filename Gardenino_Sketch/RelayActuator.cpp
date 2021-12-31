#include "RelayActuator.h"
#include "Debug.h"

RelayActuator::RelayActuator(const uint8_t &actuatorPin)
    : ActuatorPin(actuatorPin)
{
}

void RelayActuator::Init()
{
    pinMode(ActuatorPin, OUTPUT);
}

void RelayActuator::AddCondition(Condition *condition)
{
    ActuationConditions.AddElement(condition);
}

void RelayActuator::Update()
{
    bool newCondition = CheckAllConditions();
    digitalWrite(ActuatorPin, !newCondition);
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