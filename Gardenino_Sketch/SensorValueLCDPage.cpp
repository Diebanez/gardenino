#include "SensorValueLCDPage.h"

SensorValueLCDPage::SensorValueLCDPage(Sensor* sensor)
{
	TargetSensor = sensor;
}

void SensorValueLCDPage::PrintPage(LiquidCrystal_I2C& lcd)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(TargetSensor->GetName());
	lcd.setCursor(0, 1);
	lcd.print(TargetSensor->GetValue());
}

void SensorValueLCDPage::Update(LiquidCrystal_I2C& lcd)
{
	if (!TargetSensor->HasChanged())
	{
		return;
	}

	lcd.setCursor(0, 1);
	lcd.print(TargetSensor->GetValue());
}