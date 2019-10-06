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

#ifndef ECHO_GPIO_H_
#define ECHO_GPIO_H_

#define GPIO_ECHO_IN_PROGRESS   0
#define GPIO_LOW_POWER          1
#define GPIO_BUTTON             2

enum GpioMode { 
    kGpioModeNone = 0,
    kGpioModeInput, 
    kGpioModeOutput, 
    kGpioModePwm,

    kGpioModeCount
};

enum GpioDirection {
    kGpioLow = 0,
    kGpioHigh
};

void Gpio_Create(void);

/**
 * Sets the GPIO mode for the specified GPIO pin.
 * 
 * There are three modes: Input, Output and PWM.
 * 
 * @param pin the GPIO pin to be set
 * @param mode the GPIO mode to be set
 * @return 0 on success, EINVAL if the pin is out of range or incorrect mode 
 *         value.
 */
int Gpio_SetMode(int pin, enum GpioMode mode);

/**
 * Sets the value for the specified output pin.
 * 
 * If the specified pin is configured as PWM mode, the value kGpioHigh will 
 * start the PWM and the value kGpioLow will stop it.
 * 
 * @param pin the GPIO pin for the output
 * @param value kGpioLow or kGpioHigh
 * @return 0 on success, < 0 on error. 
 */
int Gpio_Output(int pin, int value);

/**
 * Returns the value the specified GPIO pin
 * 
 * @param pin the GPIO pin to be read.
 * @return the value of pin
 */
int Gpio_Input(int pin);

/**
 * Set up a PWM GPIO pin
 * 
 * @param pin the GPIO pin to be set.
 * @param frequency_hz the frequency of the pulse in Hertz
 * @param duty_cycle the propotion of on time to the period
 * 
 * @return 0 on success, < 0 on error. 
 */
int Gpio_SetupPwm(int pin, int frequency_hz, int duty_cycle);

#endif  // ECHO_GPIO_H_