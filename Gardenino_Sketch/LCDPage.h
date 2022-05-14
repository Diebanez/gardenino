#pragma once

#include <LiquidCrystal_I2C.h>

class LCDPage
{
public:
	virtual void PrintPage(LiquidCrystal_I2C& lcd) = 0;
	virtual void Update(LiquidCrystal_I2C& lcd) = 0;
};