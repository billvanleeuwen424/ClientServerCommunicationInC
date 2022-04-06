#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>

struct packet{
    char data[1024];
    int size;
};


int packetSize = sizeof(struct packet);