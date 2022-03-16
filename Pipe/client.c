

#include <stdio.h>
#include <unistd.h>


#define CLIENTFIFO "clientfifo"
#define SERVERFIFO  "serverfifo"


int main(){

    if(access(CLIENTFIFO, W_OK) == 0){
        printf("Client to server fifo does not exist, or the permission have been configured incorrectlty. Exiting.\n");
    }

    if(access(SERVERFIFO, R_OK) == 0){
         printf("Server to Client fifo does not exist, or the permission have been configured incorrectlty. Exiting.\n");
    }
}