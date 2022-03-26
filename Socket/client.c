#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main(){

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(57505); //50000 + last 4 of student num
    server.sin_addr.s_addr = inet_addr("192.168.0.190");

    //create socket
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);

    if(connect(clientfd, (struct sockaddr*) &server, sizeof(server)) < 0){
        fprintf(stderr, "Connection error. %s\n", strerror(errno));
        exit(-1);
    }



    close(clientfd);
}