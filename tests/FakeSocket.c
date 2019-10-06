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
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include "FakeSocket.h"

struct Socket {
    bool is_null;
    bool is_read_timedout;
    bool is_read_error;
    bool is_write_error;
    bool is_wrong_counter;
    char data[64];
} s_sock;

void FakeSocket_Setup(bool is_null, bool is_read_timedout, bool is_read_error,
        bool is_write_error, bool is_wrong_counter)
{
    s_sock.is_null = is_null;
    s_sock.is_read_timedout = is_read_timedout;
    s_sock.is_read_error = is_read_error;
    s_sock.is_write_error = is_write_error;
    s_sock.is_wrong_counter = is_wrong_counter;
}        

struct Socket* Socket_Create(const char *url, const char *port, int read_timeout_ms)
{
    return !s_sock.is_null ? &s_sock : NULL;
}

int Socket_Write(struct Socket* sock, const void* data, int size)
{
    if (s_sock.is_write_error)
        return -1;

    memcpy(s_sock.data, data, size);
    return size;
}

int Socket_Read(struct Socket* sock, void* data, int size)
{
    if (s_sock.is_read_error)
        return 0;

    if (s_sock.is_read_timedout)
        return -EAGAIN;

    if (s_sock.is_wrong_counter) {
        uint16_t wrong_counter = -1;
        memcpy(data, &wrong_counter, sizeof(wrong_counter));

        return size;
    }

    memcpy(data, s_sock.data, size);
    return size;
}

void Socket_Destroy(struct Socket* sock)
{
    return;
}