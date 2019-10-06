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
#include "Gpio.h"
}

TEST_GROUP(Gpio)
{
   void setup()
   {
      Gpio_Create();
   }
};

TEST(Gpio, OutputGpio0ToHigh)
{
   CHECK_EQUAL(0, Gpio_SetMode(0, kGpioModeOutput));
   CHECK_EQUAL(0, Gpio_Output(0, kGpioHigh));
   CHECK_EQUAL(1, Gpio_Input(0));
}

TEST(Gpio, OutputOneGpioToHighAndOneGpioToLow)
{
    Gpio_SetMode(0, kGpioModeOutput);
    Gpio_SetMode(1, kGpioModeOutput);

    Gpio_Output(0, kGpioHigh);
    Gpio_Output(1, kGpioLow);

    CHECK_EQUAL(1, Gpio_Input(0));
    CHECK_EQUAL(0, Gpio_Input(1));
}

TEST(Gpio, RejectModeSettingForOutOfRangePin)
{
   CHECK_EQUAL(-EINVAL, Gpio_SetMode(3, kGpioModeOutput));
   CHECK_EQUAL(-EINVAL, Gpio_SetMode(-1, kGpioModeOutput));
}

TEST(Gpio, RejectWrongMode)
{
   CHECK_EQUAL(-EINVAL, Gpio_SetMode(0, kGpioModeCount));
   CHECK_EQUAL(-EINVAL, Gpio_SetMode(-1, kGpioModeOutput));
}

TEST(Gpio, RejectToDriveOutputForOutOfRangePin)
{
   Gpio_SetMode(0, kGpioModeOutput);
   CHECK_EQUAL(-EINVAL, Gpio_Output(3, kGpioHigh));
}

TEST(Gpio, RejectToDriveOutputIfModeIsNotOutput)
{
   Gpio_SetMode(0, kGpioModeInput);
   CHECK_EQUAL(-EINVAL, Gpio_Output(0, kGpioHigh));
}

TEST(Gpio, RejectToReadInputForOutOfRangePin)
{
   Gpio_SetMode(0, kGpioModeInput);
   CHECK_EQUAL(-EINVAL, Gpio_Input(3));
}

TEST(Gpio, SetupPwmWith2HzFrequencyAtOneFourthDutyCycle)
{
   Gpio_SetMode(1, kGpioModePwm);
   CHECK_EQUAL(0, Gpio_SetupPwm(1, 2, 25));
}

TEST(Gpio, RejectPwmSettingsIfModeIsNotPwm)
{
   Gpio_SetMode(1, kGpioModeInput);
   
   CHECK_EQUAL(-EINVAL, Gpio_SetupPwm(1, 2, 25));
}

TEST(Gpio, RejectPwmSettingsForOutOfRangePin)
{
   CHECK_EQUAL(-EINVAL, Gpio_SetupPwm(3, 2, 25));
}

TEST(Gpio, RejectPwmSettingsForOutOfRangeDutyCycle)
{
   Gpio_SetMode(2, kGpioModePwm);

   CHECK_EQUAL(-EINVAL, Gpio_SetupPwm(2, 2, -1));
   CHECK_EQUAL(-EINVAL, Gpio_SetupPwm(2, 2, 101));
}
