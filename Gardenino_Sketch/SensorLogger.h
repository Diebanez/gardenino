#pragma once

#include "Clock.h"
#include "Collection.h"
#include "Sensor.h"


#define LOGS_FOLDER "/Logs"

class SensorLogger
{
public:
	SensorLogger(Clock* logClock);
	void AddSensorToLog(Sensor* target);
	void Init(TimeSpan LogSpan);
	void Update();

private:
	void Log();

	Clock* LogClock;
	Collection<Sensor> SensorToLog;
	DateTime LastLogTime;
	TimeSpan PrintLogSpan;
};