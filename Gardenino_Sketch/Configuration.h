#pragma once

#include "Clock.h"
#include "Range.h"

class Configuration
{
public:
  Configuration();
  bool Load();

  TimeSpan GetDataLogOffset() const;
  Range<float> GetSoilHumidityRange() const;
  Range<float> GetAirHumidityRange() const;
  Range<float> GetAirTemperatureRange() const;
  Range<DateTime> GetActivationTime() const;

private:
  TimeSpan DataLogOffset;
  Range<float> SoilHumidityRange;
  Range<float> AirHumidityRange;
  Range<float> AirTemperatureRange;
  Range<DateTime> ActivationTime;
};
