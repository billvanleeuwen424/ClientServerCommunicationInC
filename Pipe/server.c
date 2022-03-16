#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

#define CLIENTFIFO "clientfifo"
#define SERVERFIFO  "serverfifo"

int main(){

    /*check if can read from client, and write to server fifo*/
    if(access(CLIENTFIFO, R_OK) != 0){
        printf("Client to server fifo does not exist, or the permission have been configured incorrectlty. Exiting.\n");
        mkfifo(CLIENTFIFO, 0777);
    }

    if(access(SERVERFIFO, W_OK) != 0){
        printf("Server to Client fifo does not exist, or the permission have been configured incorrectlty. Exiting.\n");
        mkfifo(SERVERFIFO, 0777);
        
    }

    

    //777 permissions temporarily
}