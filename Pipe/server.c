#include <sys/stat.h>

int main(){
    
    char *clientToServerFifo;
    char *serverToClientFifo;

    mkfifo(const char *pathname, mode_t mode);
}