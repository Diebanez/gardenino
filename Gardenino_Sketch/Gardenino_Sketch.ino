#define ENABLE_SD_STORING
#define ENABLE_SENSOR_LOGGING

#define SD_CHIP_SELECT 53
#define SWAP_PAGE_PIN 2

#include "AnalogSensor.h"
#include "Clock.h"
#include "ClockLCDPage.h"
#include "Collection.h"
#include "Configuration.h"
#include "DHTSensor.h"
#include "Debug.h"
#include "LCDManager.h"
#include "MaxActivationTimeCondition.h"
#include "MinOffsetTimeCondition.h"
#include "RelayActuator.h"
#include "Sensor.h"
#include "SensorLogger.h"
#include "SensorMediumInRangeCondition.h"
#include "SensorValueInRangeCondition.h"
#include "SensorValueLCDPage.h"
#include "TimeCondition.h"

#include <SD.h>

Clock GlobalClock;
LCDManager DisplayManger(0x27, 16, 2, new ClockLCDPage(&GlobalClock));
Configuration Config;

#if defined(ENABLE_SD_STORING) && defined(ENABLE_SENSOR_LOGGING)
SensorLogger DataLogger(&GlobalClock);
#endif
Collection<Sensor> SoilHumiditySensors;
DHT DhtSensor(5, DHT22);
DHTSensor AirHumiditySensor(&DhtSensor, "Air humidity", 0);
DHTSensor AirTemperatureSensor(&DhtSensor, "Air temperature", 1);
bool bPreviousSwapState = false;

RelayActuator PumpActuator(3, &GlobalClock);

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

	SERIAL_LOG(F("Loading configuration ..."))

#ifdef ENABLE_SD_STORING
	if (!Config.Load())
	{
		SERIAL_LOG(F("Error while loading configuration"))
		while (true)
		{
			delay(100);
		}
	}
#else
	Config.LoadDefaultConfiguration();
#endif
	SERIAL_LOG(F("Loaded configuration"))
	SERIAL_LOG("Data log offset" + String(Config.GetDataLogOffset().hours()) + ":" +
			   String(Config.GetDataLogOffset().minutes()) + ":" + String(Config.GetDataLogOffset().seconds()))
	SERIAL_LOG("Activation soil humidity range [" + String(Config.GetSoilHumidityRange().Start) + "-" +
			   String(Config.GetSoilHumidityRange().End) + "]")
	SERIAL_LOG("Activation air humidity range [" + String(Config.GetAirHumidityRange().Start) + "-" +
			   String(Config.GetAirHumidityRange().End) + "]")
	SERIAL_LOG("Activation air temperature range [" + String(Config.GetAirTemperatureRange().Start) + "-" +
			   String(Config.GetAirTemperatureRange().End) + "]")
	SERIAL_LOG("Activation time [" + String(Config.GetActivationTime().Start.hour()) + ":" +
			   String(Config.GetActivationTime().Start.minute()) + "-" + String(Config.GetActivationTime().End.hour()) +
			   ":" + String(Config.GetActivationTime().End.minute()) + "]")

	SERIAL_LOG(F("Initializing sensors ..."))
	SoilHumiditySensors.AddElement(new AnalogSensor("Soil Sensor 1", 0));
	SoilHumiditySensors.AddElement(new AnalogSensor("Soil Sensor 2", 1));
	SoilHumiditySensors.AddElement(new AnalogSensor("Soil Sensor 3", 2));
	SoilHumiditySensors.AddElement(new AnalogSensor("Soil Sensor 4", 3));
	SoilHumiditySensors.AddElement(new AnalogSensor("Soil Sensor 5", 4));

	for (int i = 0; i < SoilHumiditySensors.GetElementsCount(); i++)
	{
		Sensor* configuringSensor = SoilHumiditySensors.GetElement(i);
		configuringSensor->Update();
		DisplayManger.AddPage(new SensorValueLCDPage(configuringSensor));
#if defined(ENABLE_SD_STORING) && defined(ENABLE_SENSOR_LOGGING)
		DataLogger.AddSensorToLog(configuringSensor);
#endif
	}

	DhtSensor.begin();

	AirHumiditySensor.Update();
	DisplayManger.AddPage(new SensorValueLCDPage(&AirHumiditySensor));
#if defined(ENABLE_SD_STORING) && defined(ENABLE_SENSOR_LOGGING)
	DataLogger.AddSensorToLog(&AirHumiditySensor);
#endif

	AirTemperatureSensor.Update();
	DisplayManger.AddPage(new SensorValueLCDPage(&AirTemperatureSensor));
#if defined(ENABLE_SD_STORING) && defined(ENABLE_SENSOR_LOGGING)
	DataLogger.AddSensorToLog(&AirTemperatureSensor);
#endif

	SERIAL_LOG(F("Sensors initialized"))

	SERIAL_LOG(F("Initializing sensors logger ..."))
#if defined(ENABLE_SD_STORING) && defined(ENABLE_SENSOR_LOGGING)
	DataLogger.Init(Config.GetDataLogOffset());
#endif
	SERIAL_LOG(F("Sensors logger initialized"))

	SERIAL_LOG(F("Initializing pump actuator ..."))
	PumpActuator.Init();
	PumpActuator.AddCondition(new SensorValueInRangeCondition(&AirHumiditySensor, Config.GetAirHumidityRange()));
	PumpActuator.AddCondition(new SensorValueInRangeCondition(&AirTemperatureSensor, Config.GetAirTemperatureRange()));
	PumpActuator.AddCondition(new TimeCondition(&GlobalClock, Config.GetActivationTime()));
	PumpActuator.AddCondition(new SensorMediumInRangeCondition(&SoilHumiditySensors, Config.GetSoilHumidityRange()));
	PumpActuator.AddCondition(new MaxActivationTimeCondition(&GlobalClock, &PumpActuator, Config.GetMaxActiveTime()));
	PumpActuator.AddCondition(new MinOffsetTimeCondition(&GlobalClock, &PumpActuator, Config.GetMinOffsetTime()));

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
#if defined(ENABLE_SD_STORING) && defined(ENABLE_SENSOR_LOGGING)
	DataLogger.Update();
#endif

	delay(100);
}