#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#include <sys/types.h>

#define CLIENTFIFO "clientfifo"
#define SERVERFIFO  "serverfifo"

int main(){
    
    int serverFileDescriptor, clientFileDescriptor;

    /*clear errno*/
    errno = 0;

    /*check if can read from client, and write to server fifo*/
    if(access(CLIENTFIFO, R_OK) != 0){
        printf("Client to server fifo does not exist, or the permission have been configured incorrectlty.\n");
        printf("Attempting to create new fifo");

            
        if(mkfifo(CLIENTFIFO,S_IRUSR | S_IWUSR | S_IWGRP) == -1){  //pg 913 Linux Programming Interface for permissions
            fprintf(stderr, "Error building client-to-server fifo. %s, Exiting.\n", strerror(errno));
            exit(-1);
        }
    }
    if(access(SERVERFIFO, W_OK) != 0){
        printf("Server to Client fifo does not exist, or the permission have been configured incorrectlty.\n");
        printf("Attempting to create new fifo");

        if(mkfifo(SERVERFIFO,S_IRUSR | S_IWUSR | S_IWGRP) == -1){
            fprintf(stderr, "Error building server-to-client fifo. %s, Exiting.\n", strerror(errno));
            exit(-1);
        }
    }

    /*clear errno*/
    errno = 0;

    /*open write only*/
    serverFileDescriptor = open(SERVERFIFO, O_WRONLY);
    if(serverFileDescriptor == -1){
        fprintf(stderr, "Error opening Server Fifo. %s\n", strerror(errno));
        exit(-1);
    }

    /*open read only*/
    clientFileDescriptor = open(CLIENTFIFO, O_RDONLY);
    if(clientFileDescriptor == -1){
        fprintf(stderr, "Error opening Client Fifo. %s\n", strerror(errno));
        exit(-1);
    }

    write(serverFileDescriptor,"yo\n",4);
    





    char filename[256];
    read(clientFileDescriptor,filename,256);

    printf("Filename: %s", filename);






    /*close the fifos*/
    close(serverFileDescriptor);
    close(clientFileDescriptor);
}