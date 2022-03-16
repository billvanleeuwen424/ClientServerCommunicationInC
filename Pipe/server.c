#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define CLIENTFIFO "clientfifo"
#define SERVERFIFO  "serverfifo"

int main(){
    

    /*check if can read from client, and write to server fifo*/
    if(access(CLIENTFIFO, R_OK) != 0){
        printf("Client to server fifo does not exist, or the permission have been configured incorrectlty. Exiting.\n");

            
        if(mkfifo(CLIENTFIFO, S_IRUSR | S_IWUSR | S_IWGRP) == -1){  //pg 913 Linux Programming Interface
            fprintf(stderr, "Error building client-to-server fifo. %d, Exiting.\n", errno);
            exit(-1);
        }
    }

    if(access(SERVERFIFO, W_OK) != 0){
        printf("Server to Client fifo does not exist, or the permission have been configured incorrectlty. Exiting.\n");

        if(mkfifo(SERVERFIFO, S_IRUSR | S_IWUSR | S_IWGRP) == -1){
            fprintf(stderr, "Error building server-to-client fifo. %d, Exiting.\n", errno);
            exit(-1);
        }
    }

    

    
}