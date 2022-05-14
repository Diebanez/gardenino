#include "SensorMediumInRangeCondition.h"

SensorMediumInRangeCondition::SensorMediumInRangeCondition(Collection<Sensor>* sensors, Range<float> actuationRange)
	: Sensors(sensors), ActuationRange(actuationRange)
{
}

bool SensorMediumInRangeCondition::Evaluate()
{
	float medium = 0;

	for (int i = 0; i < Sensors->GetElementsCount(); i++)
	{
		medium += Sensors->GetElement(i)->GetValue();
	}

	medium /= Sensors->GetElementsCount();

	return medium >= ActuationRange.Start && medium <= ActuationRange.End;
}