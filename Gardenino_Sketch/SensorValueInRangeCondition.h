#pragma once

#include "Condition.h"
#include "Range.h"
#include "Sensor.h"


class SensorValueInRangeCondition : public Condition
{
public:
	SensorValueInRangeCondition(Sensor* targetSensor, Range<float> actuationRange);
	virtual bool Evaluate() override;

private:
	Sensor* TargetSensor;
	Range<float> ActuationRange;
};