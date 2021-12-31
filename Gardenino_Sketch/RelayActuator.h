#pragma once

#include <stdint.h>
#include <Arduino.h>
#include "Collection.h"
#include "Condition.h"

class RelayActuator
{
public:
    RelayActuator(const uint8_t &actuatorPin);
    void Init();
    void AddCondition(Condition *condition);
    void Update();

private:
    bool CheckAllConditions();

    uint8_t ActuatorPin;
    Collection<Condition> ActuationConditions;
};