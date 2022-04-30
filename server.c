/*
Name: Lab4 (server)
Authour: William Van Leeuwen - 0697505
Purpose: a simple file transfer program using sockets

How to use:
    step 1: ./server
    step 2: now that the server is running:
            ./client [file you wish to transfer to the server directory]

Params: none.

Required: See include statements below. Most are in the common.c file
*/

#include "common.h"
#include <signal.h>
int main(){

    errno = 0;

    /*define socket*/
    int serverfd;
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(57505); //50000 + last 4 of student num
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    struct sockaddr_in client;
    int sizeclient = sizeof(client);

    /*create socket*/
    if((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        fprintf(stderr, "socket create errror. %s\n", strerror(errno));
        exit(-1);
    }
    /*bind*/
    if(bind(serverfd, (struct sockaddr*) &server, sizeof(server)) < 0){
        fprintf(stderr, "bind errror. %s\n", strerror(errno));
        exit(-1);
    }



    char filename[256];
    char *pfilename;
    int outFiled;
    int clientfd;

    struct packet packet;
    struct packet *packetP = &packet;


    //loop forever
    while(1){
        
        /*wait for connection*/
        if(listen(serverfd, 1) < 0){
            fprintf(stderr, "listen error. %s\n", strerror(errno));
            close(serverfd);
            exit(-1);
        }
        clientfd = accept(serverfd, (struct sockaddr*) &client, &sizeclient);
        if(clientfd < 0){
            fprintf(stderr, "accept error. %s\n", strerror(errno));
            close(clientfd);
            close(serverfd);
            exit(-1);
        }


        /* Read the filename*/
        read(clientfd, packetP, packetSize);
        strcpy(filename,packet.data);
        
        errno = 0;

        /*error with file open. close connection*/
        if((outFiled = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0){
            fprintf(stderr, "open file error. %s\n", strerror(errno));
            close(outFiled);
            close(clientfd);
            close(serverfd);
            exit(-1);
        }


        /*read data from socket, output to file*/
        do{
            errno = 0;
            if(read(clientfd, packetP, packetSize) < 0){
                fprintf(stderr, "read socket error. %s\n", strerror(errno));
                close(outFiled);
                close(clientfd);
                close(serverfd);
                exit(-1);
            }
            if(write(outFiled, packet.data, packet.size) < 0){
                fprintf(stderr, "write to file error. %s\n", strerror(errno));
                close(outFiled);
                close(clientfd);
                close(serverfd);
                exit(-1);
            }
        } while (packet.size == 1024);  /*read until input is < 1024*/


        printf("%s has been transfered successfully.\n", filename);

        /*write an empty ok message*/
        write(clientfd, (void*)0,1);
        
        /*close fd's*/
        close(outFiled);
        close(clientfd);

        strcpy(packet.data, "");
        packet.size = 0;
    }



    close(serverfd);
    exit(1);
}