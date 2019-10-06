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

#include "LedDriver.h"
#include "Gpio.h"

#define PWM_FREQ_HZ         2
#define PWM_DUTY_CYCLE      25

void LedDriver_Create(void)
{
    // White LED to indicate the echoing is in progress
    Gpio_SetMode(GPIO_ECHO_IN_PROGRESS, kGpioModeOutput);

    // Red LED to indicate low power
    Gpio_SetMode(GPIO_LOW_POWER, kGpioModePwm);
    Gpio_SetupPwm(GPIO_LOW_POWER, PWM_FREQ_HZ, PWM_DUTY_CYCLE);
}

int LedDriver_TurnOn(int number)
{
    return Gpio_Output(number, kGpioHigh);
}

int LedDriver_TurnOff(int number)
{
    return Gpio_Output(number, kGpioLow);
}

void LedDriver_Destroy(void)
{

}
