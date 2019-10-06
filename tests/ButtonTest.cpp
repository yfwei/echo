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
#include "Button.h"
}

TEST_GROUP(Button)
{
   void setup()
   {
       Gpio_Create();
       Button_Create();
   }

   void teardown()
   {
       Button_Destroy();
   }
};
 
TEST(Button, GpioTwoDirectionIsInputAfterInitialization)
{
    CHECK_EQUAL(kGpioModeInput, GpioSpy_GetMode(2));
}

TEST(Button, CheckButtonIsPressed)
{
    Gpio_Output(GPIO_BUTTON, kGpioLow);

    CHECK_EQUAL(true, Button_IsPressed());
}

TEST(Button, CheckButtonIsReleased)
{
    Gpio_Output(GPIO_BUTTON, kGpioHigh);

    CHECK_EQUAL(false, Button_IsPressed());
}
