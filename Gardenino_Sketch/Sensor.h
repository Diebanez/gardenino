#pragma once

#include <Arduino.h>

class Sensor
{
public:
    String GetName() const;
    bool HasChanged() const;

    virtual float GetValue() = 0;
    virtual void Update() = 0;

protected:
    Sensor(const String &name);

    bool bHasChanged;

private:
    String Name;
};