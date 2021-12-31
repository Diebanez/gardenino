#include "Sensor.h"

String Sensor::GetName() const
{
    return Name;
}
bool Sensor::HasChanged() const
{
    return bHasChanged;
}

Sensor::Sensor(const String &name)
    : Name(name), bHasChanged(false)
{
    Name = name;
}