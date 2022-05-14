#pragma once

#include "Clock.h"
#include "Range.h"

class Configuration
{
public:
	Configuration();
	bool Load();
	void LoadDefaultConfiguration();

	TimeSpan GetDataLogOffset() const;
	Range<float> GetSoilHumidityRange() const;
	Range<float> GetAirHumidityRange() const;
	Range<float> GetAirTemperatureRange() const;
	Range<DateTime> GetActivationTime() const;
	float GetMaxActiveTime() const;
	float GetMinOffsetTime() const;

private:
	TimeSpan DataLogOffset;
	Range<float> SoilHumidityRange;
	Range<float> AirHumidityRange;
	Range<float> AirTemperatureRange;
	Range<DateTime> ActivationTime;
	int MaxActiveTime;
	int MinOffsetTime;
};
