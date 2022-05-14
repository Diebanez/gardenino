#pragma once

#include "Sensor.h"

#include <stdint.h>


class AnalogSensor : public Sensor
{
public:
	AnalogSensor(const String& name, const uint8_t& pin);

	virtual float GetValue() override;
	virtual void Update() override;

private:
	uint8_t Pin;
	float Value;
};