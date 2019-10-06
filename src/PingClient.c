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
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdlib.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>

#include "PingClient.h"
#include "Socket.h"
#include "TimeService.h"

#define TIMEOUT_MS      500
#define INTERVAL_MS     1000

static struct Socket *s_sock = NULL;
static uint16_t s_counter = 0;

int PingClient_Create(const char *url, const char *port_num)
{
    s_sock = Socket_Create(url, port_num, TIMEOUT_MS);
    if (s_sock == NULL)
        return -1;

    s_counter = 0;

    return 0;
}

int PingClient_Ping(void)
{
    if (s_sock == NULL) return -1;

    s_counter = htons(s_counter);
    if (Socket_Write(s_sock, &s_counter, sizeof(s_counter)) != sizeof(s_counter)) {
        perror("Failed to send");
        return -1;
    }
    s_counter = ntohs(s_counter);

    uint16_t ack_counter = 0;
    int num_bytes_read = Socket_Read(s_sock, &ack_counter, sizeof(ack_counter));
    if (num_bytes_read == sizeof(ack_counter)) {
        ack_counter = ntohs(ack_counter);
        if (ack_counter == s_counter) {
            ++s_counter;
            TimeService_DelayMillis(INTERVAL_MS);
        } else {
            fprintf(stderr, "Server returns the wrong value.\n");
        }
    } else if (num_bytes_read == -EAGAIN){
        fprintf(stderr, "Read timed out.\n");
    } else {
        return -1;
    }

    return s_counter;
}

void PingClient_Destroy(void)
{
    if (s_sock != NULL) {
        Socket_Destroy(s_sock);
        s_sock = NULL;
    }

    s_counter = 0;
}
