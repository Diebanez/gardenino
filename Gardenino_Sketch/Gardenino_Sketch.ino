#define ENABLE_CONFIGURATION
#define ENABLE_DEBUG_LOG

#include "Debug.h"
#include "Clock.h"
#include "LCDManager.h"
#include "ClockLCDPage.h"
#include <SD.h>
#ifdef ENABLE_CONFIGURATION
#include "Configuration.h"
#endif
#include "SensorLogger.h"
#include "Collection.h"
#include "Sensor.h"
#include "AnalogSensor.h"
#include "DHTSensor.h"
#include "SensorValueLCDPage.h"
#include "RelayActuator.h"
#include "SensorValueInRangeCondition.h"
#include "SensorMediumInRangeCondition.h"
#include "TimeCondition.h"

#define SD_CHIP_SELECT 53
#define SWAP_PAGE_PIN 2

Clock GlobalClock;
LCDManager DisplayManger(0x27, 16, 2, new ClockLCDPage(&GlobalClock));
#ifdef ENABLE_CONFIGURATION
Configuration Config;
#endif
SensorLogger DataLogger(&GlobalClock);
Collection<Sensor> SoilHumiditySensors;
DHT DhtSensor(5, DHT22);
DHTSensor AirHumiditySensor(&DhtSensor, "Air humidity", 0);
DHTSensor AirTemperatureSensor(&DhtSensor, "Air temperature", 1);
bool bPreviousSwapState = false;

RelayActuator PumpActuator(3);

void setup()
{
  Serial.begin(115200);

  SERIAL_LOG(F("Initializing clock ..."))
  if (!GlobalClock.Init())
  {
    SERIAL_LOG(F("Error initializing clock"))
    while (true)
    {
      delay(100);
    }
  }
  SERIAL_LOG(F("Clock initialized"))

  SERIAL_LOG(F("Initializing display ..."))
  DisplayManger.Init();
  SERIAL_LOG(F("Display initialized"))

  SERIAL_LOG(F("Initializing SD ..."))
  while (!SD.begin(SD_CHIP_SELECT))
  {
    SERIAL_LOG(F("Failed to initialize SD library"))
    delay(1000);
  }
  SERIAL_LOG(F("SD Initialized"))

#ifdef ENABLE_CONFIGURATION
  SERIAL_LOG(F("Loading configuration ..."))
  if (!Config.Load())
  {
    SERIAL_LOG(F("Error while loading configuration"))
    while (true)
    {
      delay(100);
    }
  }
  SERIAL_LOG(F("Loaded configuration"))
  SERIAL_LOG("Data log offset" + String(Config.GetDataLogOffset().hours()) + ":" + String(Config.GetDataLogOffset().minutes()) + ":" + String(Config.GetDataLogOffset().seconds()))
  SERIAL_LOG("Activation soil humidity range [" + String(Config.GetSoilHumidityRange().Start) + "-" + String(Config.GetSoilHumidityRange().End) + "]")
  SERIAL_LOG("Activation air humidity range [" + String(Config.GetAirHumidityRange().Start) + "-" + String(Config.GetAirHumidityRange().End) + "]")
  SERIAL_LOG("Activation air temperature range [" + String(Config.GetAirTemperatureRange().Start) + "-" + String(Config.GetAirTemperatureRange().End) + "]")
  SERIAL_LOG("Activation time [" + String(Config.GetActivationTime().Start.hour()) + ":" + String(Config.GetActivationTime().Start.minute()) + "-" + String(Config.GetActivationTime().End.hour()) + ":" + String(Config.GetActivationTime().End.minute()) + "]")

#endif

  SERIAL_LOG(F("Initializing sensors ..."))
  SoilHumiditySensors.AddElement(new AnalogSensor("Soil Sensor 1", 0));
  SoilHumiditySensors.AddElement(new AnalogSensor("Soil Sensor 2", 1));
  SoilHumiditySensors.AddElement(new AnalogSensor("Soil Sensor 3", 2));
  SoilHumiditySensors.AddElement(new AnalogSensor("Soil Sensor 4", 3));
  SoilHumiditySensors.AddElement(new AnalogSensor("Soil Sensor 5", 4));

  for (int i = 0; i < SoilHumiditySensors.GetElementsCount(); i++)
  {
    Sensor *configuringSensor = SoilHumiditySensors.GetElement(i);
    configuringSensor->Update();
    DisplayManger.AddPage(new SensorValueLCDPage(configuringSensor));
    DataLogger.AddSensorToLog(configuringSensor);
  }

  DhtSensor.begin();

  AirHumiditySensor.Update();
  DisplayManger.AddPage(new SensorValueLCDPage(&AirHumiditySensor));
  DataLogger.AddSensorToLog(&AirHumiditySensor);

  AirTemperatureSensor.Update();
  DisplayManger.AddPage(new SensorValueLCDPage(&AirTemperatureSensor));
  DataLogger.AddSensorToLog(&AirTemperatureSensor);

  SERIAL_LOG(F("Sensors initialized"))

  SERIAL_LOG(F("Initializing sensors logger ..."))
#ifdef ENABLE_CONFIGURATION
  DataLogger.Init(Config.GetDataLogOffset());
#else
  DataLogger.Init(TimeSpan(0, 1, 0, 0));
#endif
  SERIAL_LOG(F("Sensors logger initialized"))

  SERIAL_LOG(F("Initializing pump actuator ..."))
  PumpActuator.Init();
#ifdef ENABLE_CONFIGURATION
  PumpActuator.AddCondition(new SensorValueInRangeCondition(&AirHumiditySensor, Config.GetAirHumidityRange()));
  PumpActuator.AddCondition(new SensorValueInRangeCondition(&AirTemperatureSensor, Config.GetAirTemperatureRange()));
  PumpActuator.AddCondition(new TimeCondition(&GlobalClock, Config.GetActivationTime()));
  PumpActuator.AddCondition(new SensorMediumInRangeCondition(&SoilHumiditySensors, Config.GetSoilHumidityRange()));
#endif

  SERIAL_LOG(F("Pump actuator initialized"))
  pinMode(SWAP_PAGE_PIN, INPUT_PULLUP);
}

void loop()
{
  bool newSwapState = digitalRead(SWAP_PAGE_PIN);

  if (!newSwapState && bPreviousSwapState)
  {
    DisplayManger.SwapPage();
  }
  bPreviousSwapState = newSwapState;

  for (int i = 0; i < SoilHumiditySensors.GetElementsCount(); i++)
  {
    SoilHumiditySensors.GetElement(i)->Update();
  }
  AirHumiditySensor.Update();
  AirTemperatureSensor.Update();

  PumpActuator.Update();

  DisplayManger.Update();
  DataLogger.Update();

  delay(100);
}
