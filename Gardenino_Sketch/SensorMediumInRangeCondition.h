#pragma once

#include "Condition.h"
#include "Sensor.h"
#include "Range.h"
#include "Collection.h"

class SensorMediumInRangeCondition : public Condition
{
public:
    SensorMediumInRangeCondition(Collection<Sensor> *sensors, Range<float> actuationRange);
    virtual bool Evaluate() override;

private:
    Collection<Sensor> *Sensors;
    Range<float> ActuationRange;
};