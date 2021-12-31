#pragma once

#include "Sensor.h"
#include <stdint.h>
#include <DHT.h>

class DHTSensor : public Sensor
{
public:
    DHTSensor(DHT *targetSensor, const String &name, const int &mode);
    virtual void Update() override;
    virtual float GetValue() override;

private:
    DHT *TargetSensor;
    float Value;
    int Mode;
};