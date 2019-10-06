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

#include <errno.h>
#include <stdbool.h>
#include <string.h>

#include "Gpio.h"

#define MAX_GPIO_NUM        3

struct Gpio {
    enum GpioMode mode;
    enum GpioDirection value;

    // For PWM (Pulse Width Modulation) mode
    int frequency_hz;
    int duty_cycle;
};

static struct Gpio s_gpio_set[MAX_GPIO_NUM];

static bool IsValid(int pin)
{
    return ((pin >= 0) && (pin < MAX_GPIO_NUM));
}

void Gpio_Create(void)
{
    memset(s_gpio_set, 0x00, sizeof(s_gpio_set));
}

int Gpio_SetMode(int pin, enum GpioMode mode)
{
    if (!IsValid(pin))
        return -EINVAL;

    if ((mode < 0) || (mode >= kGpioModeCount))
        return -EINVAL;

    s_gpio_set[pin].mode = mode;

    return 0;
}

int Gpio_Output(int pin, int value)
{
    if (!IsValid(pin))
        return -EINVAL;

    if (s_gpio_set[pin].mode == kGpioModeInput)
        return -EINVAL;

    s_gpio_set[pin].value = value;

    return 0;
}

int Gpio_Input(int pin)
{
    if (!IsValid(pin))
        return -EINVAL;

    return s_gpio_set[pin].value;
}

int Gpio_SetupPwm(int pin, int frequency_hz, int duty_cycle)
{
    if (!IsValid(pin))
        return -EINVAL;

    if (s_gpio_set[pin].mode != kGpioModePwm)
        return -EINVAL;

    if ((duty_cycle < 0) || (duty_cycle > 100))
        return -EINVAL;        

    s_gpio_set[pin].frequency_hz = frequency_hz;
    s_gpio_set[pin].duty_cycle = duty_cycle;

    return 0;
}
