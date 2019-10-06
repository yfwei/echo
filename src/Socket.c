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

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>

#include "Socket.h"

struct Socket {
    int fd;
};

struct Socket* Socket_Create(const char *url, const char *port, int read_timeout_ms)
{
    struct addrinfo hints;
    memset(&hints, 0x00, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_NUMERICSERV;

    int result = 0;
    struct addrinfo *service_info;
    if ((result = getaddrinfo(url, port, &hints, &service_info)) != 0) {
        fprintf(stderr, "Failed to resolve the address: %s\n", gai_strerror(result));
        return NULL;
    }

    struct Socket *sock = malloc(sizeof(struct Socket));
    sock->fd = -1;
    struct addrinfo *service;
    for (service = service_info; service != NULL; service = service->ai_next) {
        sock->fd = socket(service->ai_family, service->ai_socktype, service->ai_protocol);
        if (sock->fd == -1)
            continue;

        struct timeval timeout = {.tv_sec = 0, .tv_usec = read_timeout_ms * 1000};
        if (setsockopt(sock->fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))) {
            perror("Failed to set receiving timeout");
            break;
        }

        if (connect(sock->fd, service->ai_addr, service->ai_addrlen) != -1)
            break;

        close(sock->fd);
    }

    freeaddrinfo(service_info);
    if (sock->fd == -1) {
        free(sock);
        return NULL;
    }

    return sock;
}

int Socket_Write(struct Socket* sock, const void* data, int size)
{
    return write(sock->fd, data, size);
}

int Socket_Read(struct Socket* sock, void* data, int size)
{
    int num_bytes_read = read(sock->fd, data, size);
    if (num_bytes_read == -1)
        return -errno;

    return num_bytes_read;
}

void Socket_Destroy(struct Socket* sock)
{
    if (sock != NULL) {
        if (sock->fd != -1)
            close(sock->fd);
        free(sock);
    }
}
