#include <sys/stat.h>

#define CLIENTFIFO "clientfifo"
#define SERVERFIFO  "serverfifo"

int main(){


    //777 permissions temporarily
    mkfifo(CLIENTFIFO, 0777);
    mkfifo(SERVERFIFO, 0777);
}