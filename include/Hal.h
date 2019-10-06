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

#ifndef ECHO_HAL_H_
#define ECHO_HAL_H_

#include <stdbool.h>

/**
 * Returns if the device is in lower power mode.
 * 
 * @return true if the device is in lower power, otherwise false.
 */ 
bool Hal_IsLowPower(void);

/**
 * Returns if the device is ready to send echo. 
 * 
 * @return true if the device is ready, otherwise false.
 */ 
bool Hal_IsReadyToEcho(void);

/**
 * Enables/Disables low power indicator
 * 
 */ 
void Hal_IndicateLowPower(bool enabled);

/**
 * Enables/Disables echo in progress indicator
 * 
 */ 
void Hal_IndicateEchoing(bool enabled);

#endif // ECHO_HAL_H_