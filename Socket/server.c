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

#include "../struct.c"

int main(){

    errno = 0;


    //define socket
    int serverfd;
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(57505); //50000 + last 4 of student num
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    struct sockaddr_in client;
    int sizeclient = sizeof(client);

    //create socket
    if((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        fprintf(stderr, "socket create errror. %s\n", strerror(errno));
        exit(-1);
    }

    //bind and listen
    if(bind(serverfd, (struct sockaddr*) &server, sizeof(server)) < 0){
        fprintf(stderr, "bind errror. %s\n", strerror(errno));
        exit(-1);
    }
    if(listen(serverfd, 5) < 0){
        fprintf(stderr, "listen error. %s\n", strerror(errno));
        exit(-1);
    }

    //wait for connection
    int clientfd = accept(serverfd, (struct sockaddr*) &client, &sizeclient);
    if(clientfd < 0){
        fprintf(stderr, "accept error. %s\n", strerror(errno));
        exit(-1);
    }

    sleep(5);
    //printf("Yeet\n");

    char new[1024];

    read(clientfd, new, 1024);

    printf("%s", new);

    close(clientfd);
    close(serverfd);
}