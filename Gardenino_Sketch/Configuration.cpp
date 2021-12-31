#include "Configuration.h"

#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#include "Debug.h"

#define CONFIG_FILE_NAME "/CONFIG"

Configuration::Configuration()
    : DataLogOffset(0), SoilHumidityRange(0, 0), AirHumidityRange(0, 0), AirTemperatureRange(0, 0), ActivationTime(DateTime(2000, 1, 1, 0, 0, 0), DateTime(2000, 1, 1, 0, 0, 0))
{
}

bool Configuration::Load()
{
  File file = SD.open(CONFIG_FILE_NAME);

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use https://arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<384> doc;

  DeserializationError error = deserializeJson(doc, file);
  if (error)
  {
    SERIAL_LOG(F("Failed to read file, using default configuration"))
    return false;
  }

  SERIAL_LOG(F("Reading configuration"));
  DataLogOffset = TimeSpan(0, doc["DataLogOffset"]["Hour"], doc["DataLogOffset"]["Minute"], doc["DataLogOffset"]["Seconds"]);
  SoilHumidityRange = Range<float>(doc["SoilHumidityRange"]["Min"], doc["SoilHumidityRange"]["Max"]);
  AirHumidityRange = Range<float>(doc["AirHumidityRange"]["Min"], doc["AirHumidityRange"]["Max"]);
  AirTemperatureRange = Range<float>(doc["AirTemperatureRange"]["Min"], doc["AirTemperatureRange"]["Max"]);
  ActivationTime = Range<DateTime>(
      DateTime(2000, 1, 1,
               doc["ActivationTime"]["StartTime"]["Hour"],
               doc["ActivationTime"]["StartTime"]["Minute"], 0),
      DateTime(2000, 1, 1,
               doc["ActivationTime"]["EndTime"]["Hour"],
               doc["ActivationTime"]["EndTime"]["Minute"], 0));

  file.close();

  return true;
}

TimeSpan Configuration::GetDataLogOffset() const
{
  return DataLogOffset;
}

Range<float> Configuration::GetSoilHumidityRange() const
{
  return SoilHumidityRange;
}

Range<float> Configuration::GetAirHumidityRange() const
{
  return AirHumidityRange;
}

Range<float> Configuration::GetAirTemperatureRange() const
{
  return AirTemperatureRange;
}

Range<DateTime> Configuration::GetActivationTime() const
{
  return ActivationTime;
}
