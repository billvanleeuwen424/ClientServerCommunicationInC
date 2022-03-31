
#include "common.c"

int main(){

    errno = 0;


    //define socket
    int serverfd;
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(57505); //50000 + last 4 of student num
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    struct sockaddr_in client;
    int sizeclient = sizeof(client);

    //create socket
    if((serverfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        fprintf(stderr, "socket create errror. %s\n", strerror(errno));
        exit(-1);
    }

    //bind
    if(bind(serverfd, (struct sockaddr*) &server, sizeof(server)) < 0){
        fprintf(stderr, "bind errror. %s\n", strerror(errno));
        exit(-1);
    }




    while(1){
        
        if(listen(serverfd, 5) < 0){
            fprintf(stderr, "listen error. %s\n", strerror(errno));
            close(serverfd);
            exit(-1);
        }

        //wait for connection
        int clientfd = accept(serverfd, (struct sockaddr*) &client, &sizeclient);
        if(clientfd < 0){
            fprintf(stderr, "accept error. %s\n", strerror(errno));
            close(clientfd);
            close(serverfd);
            exit(-1);
        }


        char filename[256];
        char *pfilename;
        read(clientfd, filename, 256);
        /*cut all the crap off the end of the filename*/
        pfilename = strtok(filename, "\n");
        
        int outFiled;
        errno = 0;

        /*error with file open. close connection*/
        if((outFiled = open(pfilename, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0){
            fprintf(stderr, "open file error. %s\n", strerror(errno));
            close(outFiled);
            close(clientfd);
            close(serverfd);
            exit(-1);
        }

        struct packet packet;
        struct packet *packetP = &packet;

        /*read data from socket, output to file*/
        do{
            errno = 0;
            if(read(clientfd, packetP, sizeof(struct packet)) < 0){
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
        } while (packet.size == 1024);
        close(outFiled);
        close(clientfd);
    }
    close(serverfd);


    exit(1);
}