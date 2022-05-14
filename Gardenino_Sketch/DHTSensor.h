#pragma once

#include "Sensor.h"

#include <DHT.h>
#include <stdint.h>


class DHTSensor : public Sensor
{
public:
	DHTSensor(DHT* targetSensor, const String& name, const int& mode);
	virtual void Update() override;
	virtual float GetValue() override;

private:
	DHT* TargetSensor;
	float Value;
	int Mode;
};