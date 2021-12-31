#include "SensorLogger.h"

#include <SD.h>
#include "Debug.h"

SensorLogger::SensorLogger(Clock *logClock)
    : PrintLogSpan(0, 1, 0, 0), LogClock(logClock)
{
}

void SensorLogger::AddSensorToLog(Sensor *target)
{
    SensorToLog.AddElement(target);
}

void SensorLogger::Init(TimeSpan LogSpan)
{
    PrintLogSpan = LogSpan;
    Log();
}

void SensorLogger::Update()
{
    DateTime now = LogClock->GetNow();
    if (now.unixtime() - LastLogTime.unixtime() >= PrintLogSpan.totalseconds())
    {
        Log();
    }
}
void SensorLogger::Log()
{
    LastLogTime = LogClock->GetNow();
    if (!SD.exists(LOGS_FOLDER))
    {
        SD.mkdir(LOGS_FOLDER);
    }

    String FileName = LOGS_FOLDER + String("/") + String(LastLogTime.day()) + String(LastLogTime.month()) + String(LastLogTime.year()) + String(".csv");

    if (!SD.exists(FileName))
    {
        File newFile = SD.open(FileName, FILE_WRITE);

        if (newFile)
        {
            String line = "Time;";

            for (int i = 0; i < SensorToLog.GetElementsCount(); i++)
            {
                line += SensorToLog.GetElement(i)->GetName();
                line += ";";
            }

            newFile.println(line);
            newFile.close();
        }
    }

    String newLine = String(LastLogTime.hour()) + String(":") + String(LastLogTime.minute()) + String(":") + String(LastLogTime.second()) + ";";

    for (int i = 0; i < SensorToLog.GetElementsCount(); i++)
    {
        newLine += String(SensorToLog.GetElement(i)->GetValue());
        newLine += ";";
    }

    File appendFile = SD.open(FileName, FILE_WRITE);
    if (appendFile)
    {
        appendFile.println(newLine);
        appendFile.close();
    }

    SERIAL_LOG("[" + String(LastLogTime.hour()) + ":" + String(LastLogTime.minute()) + ":" + String(LastLogTime.second()) + "] Logged data to sd")
}
