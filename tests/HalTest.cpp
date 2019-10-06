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
#include "Hal.h"
#include "FakeAdcDriver.h"
#include "GpioSpy.h"
#include "Button.h"
#include "LedDriver.h"
}

TEST_GROUP(Hal)
{
   void setup()
   {
       Button_Create();
       LedDriver_Create();
   }

   void teardown()
   {
      
   }   
};
 
TEST(Hal, LowPowerIsDetected)
{
    FakeAdcDriver_SetValue(3400);

    CHECK(Hal_IsLowPower());
}

TEST(Hal, StandardPowerIsDetected)
{
    FakeAdcDriver_SetValue(3500);

    CHECK_FALSE(Hal_IsLowPower());
}

TEST(Hal, ReadyToEcho)
{
    Gpio_Output(GPIO_BUTTON, kGpioLow);

    CHECK(Hal_IsReadyToEcho());
}

TEST(Hal, NotReadyToEcho)
{
    Gpio_Output(GPIO_BUTTON, kGpioHigh);

    CHECK_FALSE(Hal_IsReadyToEcho());
}

TEST(Hal, IndicateLowPower)
{
    Hal_IndicateLowPower(true);

    CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_LOW_POWER));
}

TEST(Hal, NoLowPowerIndication)
{
    Hal_IndicateLowPower(true);
    Hal_IndicateLowPower(false);

    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_LOW_POWER));
}

TEST(Hal, IndicateEchoIsInProgress)
{
    Hal_IndicateEchoing(true);

    CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
}

TEST(Hal, NoEchoInProgressIndication)
{
    Hal_IndicateEchoing(true);
    Hal_IndicateEchoing(false);

    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
}