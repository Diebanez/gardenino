#include "SensorValueInRangeCondition.h"

SensorValueInRangeCondition::SensorValueInRangeCondition(Sensor* targetSensor, Range<float> actuationRange)
	: TargetSensor(targetSensor), ActuationRange(actuationRange)
{
}

bool SensorValueInRangeCondition::Evaluate()
{
	return TargetSensor->GetValue() >= ActuationRange.Start && TargetSensor->GetValue() <= ActuationRange.End;
}