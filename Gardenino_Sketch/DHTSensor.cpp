#include "DHTSensor.h"

#include "Debug.h"


DHTSensor::DHTSensor(DHT* targetSensor, const String& name, const int& mode)
	: Sensor(name), TargetSensor(targetSensor), Value(0), Mode(mode)
{
}

void DHTSensor::Update()
{
	bHasChanged = false;
	float newValue = 0;
	if (Mode == 0)
	{
		newValue = TargetSensor->readHumidity();
	}
	else
	{
		newValue = TargetSensor->readTemperature();
	}

	if (!isnan(newValue) && Value != newValue)
	{
		SERIAL_LOG("[" + GetName() + "] Updated value" + String(newValue))
		Value = newValue;
		bHasChanged = true;
	}
}

float DHTSensor::GetValue()
{
	return Value;
}