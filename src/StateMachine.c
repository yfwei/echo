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

#include <stdio.h>

#include "StateMachine.h"
#include "PingClient.h"
#include "Hal.h"

#define PORT_NUM        "13469"
#define SERVER_NAME     "test.ring.com"

enum SM_State {
    kStateStart = 0,
    kStateIdle,
    kStateEcho,
    kStateLowPower,

    kStateCount
};

struct SM_StateHandler {
    void (*entry)(void);
    enum SM_State (*action)(void);
    void (*exit)(void);
};

static enum SM_State SM_StartAction(void) 
{
    return kStateIdle;
}

static void SM_EchoEntry(void) 
{
    PingClient_Create(SERVER_NAME, PORT_NUM);
    Hal_IndicateEchoing(true);
}

static enum SM_State SM_EchoAction(void) 
{
    if (Hal_IsLowPower())
        return kStateLowPower;

    int counter = PingClient_Ping();
    printf("counter=%d\n", counter);
    if (counter < 0)
        return kStateIdle;

    return Hal_IsReadyToEcho() ? kStateEcho : kStateIdle;
}

static void SM_EchoExit(void) 
{
    PingClient_Destroy();
    Hal_IndicateEchoing(false);
}

static enum SM_State SM_IdleAction(void) 
{
    if (Hal_IsLowPower())
        return kStateLowPower;

    return Hal_IsReadyToEcho() ? kStateEcho : kStateIdle;
}

static void SM_LowPowerEntry(void) 
{
    Hal_IndicateLowPower(true);
}

static enum SM_State SM_LowPowerAction(void) 
{
    return Hal_IsLowPower() ? kStateLowPower : kStateIdle;
}

static void SM_LowPowerExit(void) 
{
    Hal_IndicateLowPower(false);
}

static struct SM_StateHandler s_states[kStateCount] = {
    {NULL, SM_StartAction, NULL},
    {NULL, SM_IdleAction, NULL},
    {SM_EchoEntry, SM_EchoAction, SM_EchoExit},
    {SM_LowPowerEntry, SM_LowPowerAction, SM_LowPowerExit},
};

static enum SM_State s_curr_state = kStateStart;
void StateMachine_Create(void)
{
    s_curr_state = kStateStart;
}

void StateMachine_Run(void)
{
    enum SM_State new_state = s_states[s_curr_state].action();
    if (s_curr_state != new_state) {
        if (s_states[s_curr_state].exit)
            s_states[s_curr_state].exit();
        if (s_states[new_state].entry)
            s_states[new_state].entry();

        s_curr_state = new_state;
    }
}
