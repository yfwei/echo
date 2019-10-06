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
#include "Socket.h"
}

TEST_GROUP(Socket)
{
   struct Socket *sock = NULL; 
   void setup()
   {
       sock = Socket_Create("test.ring.com", "13469", 500);
   }

   void teardown()
   {
       Socket_Destroy(sock);
   }
};
 
TEST(Socket, Create)
{
    CHECK(sock != NULL);
}

TEST(Socket, Write)
{
    uint16_t counter = 0;
    int bytes_written = Socket_Write(sock, &counter, sizeof(counter));

    CHECK_EQUAL(sizeof(counter), bytes_written);
}

