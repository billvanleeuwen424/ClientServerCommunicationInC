#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>

int main(){

    errno = 0;

    //define socket
    int socketfd;
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(57505); //50000 + last 4 of student num
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    struct sockaddr_in client;
    int sizeclient = sizeof(client);

    //create socket
    socketfd = socket(AF_UNIX, SOCK_STREAM, 0);

    //bind and listen
    if(bind(socketfd, (struct sockaddr*) &server, sizeof(server)) < 0){
        fprintf(stderr, "%s", strerror(errno));
        exit(-1);
    }
    if(listen(socketfd, 1) < 0){
        fprintf(stderr, "%s", strerror(errno));
        exit(-1);
    }

    //wait for connection
    int clientfd = accept(socketfd, (struct sockaddr*) &client, &sizeclient);
    if(clientfd < 0){
        fprintf(stderr, "%s", strerror(errno));
        exit(-1);
    }


}