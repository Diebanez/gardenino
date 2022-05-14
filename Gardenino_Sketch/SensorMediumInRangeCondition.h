#pragma once

#include "Collection.h"
#include "Condition.h"
#include "Range.h"
#include "Sensor.h"


class SensorMediumInRangeCondition : public Condition
{
public:
	SensorMediumInRangeCondition(Collection<Sensor>* sensors, Range<float> actuationRange);
	virtual bool Evaluate() override;

private:
	Collection<Sensor>* Sensors;
	Range<float> ActuationRange;
};