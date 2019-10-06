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
#include "PingClient.h"
#include "FakeSocket.h"
#include "FakeTimeService.h"
}

TEST_GROUP(PingClient)
{
   void setup()
   {
       FakeSocket_Setup(false, false, false, false, false);
   }

   void teardown()
   {
   }    
};
 
TEST(PingClient, FailToCreate)
{
    FakeSocket_Setup(true, false, false, false, false);
    CHECK_EQUAL(-1, PingClient_Create("www.google.com", "80"));
}

TEST(PingClient, ReadTimedout)
{
    PingClient_Create("www.google.com", "80");
    int counter = PingClient_Ping();

    FakeSocket_Setup(false, true, false, false, false);
    int counter2 = PingClient_Ping();
    CHECK_EQUAL(counter, counter2);
}

TEST(PingClient, FailToRead)
{
    FakeSocket_Setup(false, false, true, false, false);
    PingClient_Create("www.google.com", "80");

    CHECK_EQUAL(-1, PingClient_Ping());
}

TEST(PingClient, FailToWrite)
{
    FakeSocket_Setup(false, false, false, true, false);
    PingClient_Create("www.google.com", "80");

    CHECK_EQUAL(-1, PingClient_Ping());
}

TEST(PingClient, ReturnWrongCounter)
{
    PingClient_Create("www.google.com", "80");
    int counter = PingClient_Ping();

    FakeSocket_Setup(false, false, false, false, true);
    int counter2 = PingClient_Ping();
    CHECK_EQUAL(counter, counter2);
}

TEST(PingClient, SendEcho10Times)
{
    CHECK_EQUAL(0, PingClient_Create("www.google.com", "80"));
    for (int i = 0; i < 10; i++) {
        int counter = PingClient_Ping();
        CHECK_EQUAL(i + 1, counter);
    }
}

TEST(PingClient, RecoverFromReadTimedOut)
{
    PingClient_Create("www.google.com", "80");
    int counter = PingClient_Ping();

    FakeSocket_Setup(false, true, false, false, false);
    for (int i = 0; i < 3; i++)
        PingClient_Ping();
    
    FakeSocket_Setup(false, false, false, false, false);
    int counter2 = PingClient_Ping();
    CHECK_EQUAL(counter + 1, counter2);
}

TEST(PingClient, RecoverFromWrongCounter)
{
    PingClient_Create("www.google.com", "80");
    int counter = PingClient_Ping();

    FakeSocket_Setup(false, false, false, false, true);
    for (int i = 0; i < 3; i++)
        PingClient_Ping();
    
    FakeSocket_Setup(false, false, false, false, false);
    int counter2 = PingClient_Ping();
    CHECK_EQUAL(counter + 1, counter2);
}

TEST(PingClient, CounterIsResetAfterBeingDestroyed)
{
    PingClient_Create("www.google.com", "80");
    for (int i = 0; i < 3; i++) {
        PingClient_Ping();
    }

    int counter = PingClient_Ping();
    CHECK_TRUE(counter > 1);

    PingClient_Destroy();

    PingClient_Create("www.google.com", "80");
    counter = PingClient_Ping();
    CHECK_EQUAL(1, counter);
}
