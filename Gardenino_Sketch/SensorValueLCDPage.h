#pragma once

#include "LCDPage.h"
#include "Sensor.h"

class SensorValueLCDPage : public LCDPage
{
public:
	SensorValueLCDPage(Sensor* sensor);
	virtual void PrintPage(LiquidCrystal_I2C& lcd) override;
	virtual void Update(LiquidCrystal_I2C& lcd) override;

private:
	Sensor* TargetSensor;
};