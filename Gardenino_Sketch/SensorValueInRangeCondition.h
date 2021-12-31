#pragma once

#include "Condition.h"
#include "Sensor.h"
#include "Range.h"

class SensorValueInRangeCondition : public Condition
{
public:
    SensorValueInRangeCondition(Sensor *targetSensor, Range<float> actuationRange);
    virtual bool Evaluate() override;

private:
    Sensor *TargetSensor;
    Range<float> ActuationRange;
};