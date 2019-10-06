/* Copyright 2019 Yun-Fei Wei

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
==============================================================================*/

#include <stdio.h>

#include "Hal.h"
#include "BatteryMonitor.h"
#include "Button.h"
#include "LedDriver.h"

#define LOW_BATTERY_VOLTAGE     3500

bool Hal_IsLowPower(void)
{
    return BatteryMonitor_ReadMilliVoltage() < LOW_BATTERY_VOLTAGE;
}

bool Hal_IsReadyToEcho(void)
{
    return Button_IsPressed();
}

void Hal_IndicateLowPower(bool enabled)
{
    if (enabled)
        LedDriver_TurnOn(1);
    else
        LedDriver_TurnOff(1);
}

void Hal_IndicateEchoing(bool enabled)
{
    if (enabled)
        LedDriver_TurnOn(0);
    else
        LedDriver_TurnOff(0);    
}
