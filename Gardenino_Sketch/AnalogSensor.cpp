#include "AnalogSensor.h"
#include "Debug.h"

AnalogSensor::AnalogSensor(const String &name, const uint8_t &pin)
    : Sensor(name), Pin(pin), Value(0)
{
}

void AnalogSensor::Update()
{
    bHasChanged = false;
    float newValue = analogRead(Pin);
    newValue /= 10.24f;
    if (newValue != Value)
    {
        Value = newValue;
        SERIAL_LOG("[" + GetName() + "] Updated analog sensor " + String(Value))
        bHasChanged = true;
    }
}

float AnalogSensor::GetValue()
{
    return Value;
}