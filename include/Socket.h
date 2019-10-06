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

#ifndef ECHO_SOCKET_H_
#define ECHO_SOCKET_H_

/**
 * Creates a socket with the specified URL and the port number
 * 
 * Note that only datagram sockets are supported.
 * 
 * @param url the url to be connected.
 * @param port the port number
 * @param read_timeout_ms the receiving timeout in milliseconds.
 * @return the created datagram socket
 */
struct Socket* Socket_Create(const char *url, const char *port, int read_timeout_ms);

/**
 * Writes the specified data to the socket 
 * 
 * @param sock the socket to be written
 * @param data the data to be written to sock
 * @param size the size of data
 * @return the number of bytes written
 */
int Socket_Write(struct Socket* sock, const void* data, int size);

/**
 * Reads the data from the specified socket
 * 
 * @param sock the socket to be read
 * @param data the data buffer to be filled
 * @param size the size of data
 * @return the number of bytes read
 */
int Socket_Read(struct Socket* sock, void* data, int size);

/**
 * Destroys the specified socket
 * 
 * @param sock the socket to be destroyed
 */
void Socket_Destroy(struct Socket* sock);

#endif // ECHO_SOCKET_H_