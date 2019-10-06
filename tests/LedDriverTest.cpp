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

#include "CppUTest/TestHarness.h"

extern "C"
{
#include "GpioSpy.h"    
#include "LedDriver.h"
}

TEST_GROUP(LedDriver)
{
   void setup()
   {
        Gpio_Create();
        LedDriver_Create();
   }

   void teardown()
   {
        LedDriver_Destroy();
   }    
};

TEST(LedDriver, GpioZeroDirectionIsOutputAndValueIsLowAfterInitialization)
{
    CHECK_EQUAL(kGpioModeOutput, GpioSpy_GetMode(0));
    CHECK_EQUAL(kGpioLow, Gpio_Input(0));
}

TEST(LedDriver, GpioOneModeIsPwmAfterInitialization)
{
    CHECK_EQUAL(kGpioModePwm, GpioSpy_GetMode(1));
    CHECK_EQUAL(2, GpioSpy_GetPwmFrequency(1));
    CHECK_EQUAL(25, GpioSpy_GetPwmDutyCycle(1));
}

TEST(LedDriver, TurnOnLedZero)
{
    LedDriver_TurnOn(0);

    CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
}

TEST(LedDriver, TurnOnLedOne)
{
    LedDriver_TurnOn(1);

    CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_LOW_POWER));
}

TEST(LedDriver, TurnOffLedZero)
{
    LedDriver_TurnOff(0);

    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
}

TEST(LedDriver, TurnOffLedOne)
{
    LedDriver_TurnOff(1);

    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_LOW_POWER));
}
