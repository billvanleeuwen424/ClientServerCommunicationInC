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


    if(access(CLIENTFIFO, W_OK) != 0){
        printf("Client-to-Server fifo does not exist, or the permission have been configured incorrectlty. Exiting.\n");
        exit(-1);
    }

    if(access(SERVERFIFO, R_OK) != 0){
         printf("Server-to-Client fifo does not exist, or the permission have been configured incorrectlty. Exiting.\n");
         exit(-1);
    }


    /*clear errno*/
    errno = 0;

    /*open read only*/
    serverFileDescriptor = open(SERVERFIFO, O_RDONLY);
    if(serverFileDescriptor == -1){
        fprintf(stderr, "Error opening Server Fifo. %s", strerror(errno));
        exit(-1);
    }

    /*open write only*/
    clientFileDescriptor = open(CLIENTFIFO, O_WRONLY | O_NONBLOCK);
    if(clientFileDescriptor == -1){
        fprintf(stderr, "Error opening Client Fifo. %s", strerror(errno));
        exit(-1);
    }


    char test[5];
    read(serverFileDescriptor,test,4);

    printf("%s", test);

    /*close the fifos*/
    close(serverFileDescriptor);
    close(clientFileDescriptor);
    
}