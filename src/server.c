#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT_NUM        13469

int main(int argc, char *argv[]) 
{
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sfd == -1) {
        perror("Failed to create server socket");
        exit(-1);
    }

    struct sockaddr_in svaddr;
    struct sockaddr_in claddr;

    memset(&svaddr, 0x00, sizeof(svaddr));
    svaddr.sin_family = AF_INET;
    svaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    svaddr.sin_port = htons(PORT_NUM);

    if (bind(sfd, (struct sockaddr *)&svaddr, sizeof(svaddr)) == -1) {
        perror("Failed to bind the port");
        exit(-1);
    }

    uint16_t counter = 0;
    
    while (1) {
        socklen_t len = sizeof(struct sockaddr_in);
        int numBytes = recvfrom(sfd, &counter, sizeof(counter), 0, (struct sockaddr*)&claddr, &len);
        if (numBytes == -1) {
            perror("Failed to read");
            break;
        }

        counter = ntohs(counter);
        printf("counter=%d\n", counter);

        counter = htons(counter);
        if (sendto(sfd, &counter, sizeof(counter), 0, (struct sockaddr *)&claddr, len) != sizeof(counter)) {
            perror("Failed to send");
            break;
        }
    }

    close(sfd);

    return 0;
}
