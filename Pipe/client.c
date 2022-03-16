#include <stdio.h>
#include <unistd.h>


#define CLIENTFIFO "clientfifo"
#define SERVERFIFO  "serverfifo"


int main(){
    if(access(CLIENTFIFO, W_OK) == 0){
        printf("yes client\n");
    };
    if(access(SERVERFIFO, R_OK) == 0){
        printf("yes server\n");
    };
}