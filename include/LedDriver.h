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

#ifndef ECHO_LEDDRIVER_H_
#define ECHO_LEDDRIVER_H_

void LedDriver_Create(void);

/**
 * Turns on the specified LED
 * 
 * @param number the LED to be turned on
 * @return 0 on success, a negative number on error
 */
int LedDriver_TurnOn(int number);

/**
 * Turns off the specified LED
 * 
 * @param number the LED to be turned on
 * @return 0 on success, a negative number on error
 */
int LedDriver_TurnOff(int number);

void LedDriver_Destroy(void);


#endif // ECHO_LEDDRIVER_H_