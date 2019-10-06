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
#include "StateMachine.h"
#include "Button.h"
#include "LedDriver.h"
#include "GpioSpy.h"
#include "FakeAdcDriver.h"
#include "FakeSocket.h"
}

TEST_GROUP(StateMachine)
{
   void setup()
   {
       Gpio_Create();
       Button_Create();
       LedDriver_Create();
       StateMachine_Create();

       FakeAdcDriver_SetValue(3600);

       StateMachine_Run();

       FakeSocket_Setup(false, false, false, false, false);
   }

   void teardown()
   {
       LedDriver_Destroy();
       Button_Destroy();
   }    
};
 
TEST(StateMachine, StartToIdle)
{
    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_LOW_POWER));
}

TEST(StateMachine, IdleToEcho)
{
    Gpio_Output(GPIO_BUTTON, kGpioLow);
    StateMachine_Run();

    CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_LOW_POWER));
}

TEST(StateMachine, IdleToLowPower)
{
    FakeAdcDriver_SetValue(3400);
    StateMachine_Run();

    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
    CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_LOW_POWER));
}

TEST(StateMachine, EchoToLowPower)
{
    Gpio_Output(GPIO_BUTTON, kGpioLow);
    StateMachine_Run();

    FakeAdcDriver_SetValue(3400);
    StateMachine_Run();

    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
    CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_LOW_POWER));
}

TEST(StateMachine, LowPowerToIdle)
{
    FakeAdcDriver_SetValue(3400);
    StateMachine_Run();

    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
    CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_LOW_POWER));

    FakeAdcDriver_SetValue(3600);
    StateMachine_Run();

    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_LOW_POWER));
}

TEST(StateMachine, EchoToIdle)
{
    Gpio_Output(GPIO_BUTTON, kGpioLow);
    StateMachine_Run();

    CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_LOW_POWER));

    Gpio_Output(GPIO_BUTTON, kGpioHigh);
    StateMachine_Run();

    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_LOW_POWER));
}

TEST(StateMachine, RejectLowPowerToEcho)
{
    FakeAdcDriver_SetValue(3400);
    StateMachine_Run();

    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
    CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_LOW_POWER));    

    Gpio_Output(GPIO_BUTTON, kGpioLow);
    StateMachine_Run();

    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
    CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_LOW_POWER));
}

TEST(StateMachine, EchoToIdleDueToPingError)
{
    Gpio_Output(GPIO_BUTTON, kGpioLow);
    StateMachine_Run();

    CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_LOW_POWER));

    FakeSocket_Setup(false, false, false, true, false);
    StateMachine_Run();

    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
    CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_LOW_POWER));
}

TEST(StateMachine, KeepInEchoMode)
{
    Gpio_Output(GPIO_BUTTON, kGpioLow);

    for (int i = 0; i < 10; i++) {    
        StateMachine_Run();
        CHECK_EQUAL(kGpioHigh, Gpio_Input(GPIO_ECHO_IN_PROGRESS));
        CHECK_EQUAL(kGpioLow, Gpio_Input(GPIO_LOW_POWER));
    }
}
