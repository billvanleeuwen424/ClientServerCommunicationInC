
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

    //bind and listen
    if(bind(serverfd, (struct sockaddr*) &server, sizeof(server)) < 0){
        fprintf(stderr, "bind errror. %s\n", strerror(errno));
        exit(-1);
    }
    if(listen(serverfd, 5) < 0){
        fprintf(stderr, "listen error. %s\n", strerror(errno));
        exit(-1);
    }

    //wait for connection
    int clientfd = accept(serverfd, (struct sockaddr*) &client, &sizeclient);
    if(clientfd < 0){
        fprintf(stderr, "accept error. %s\n", strerror(errno));
        exit(-1);
    }

    /*get the filename*/
    char filename[256];
    if(read(clientfd, filename, 256) == 0){
        fprintf(stderr, "filename read error. %s\n", strerror(errno));
        exit(-1);
    }


    /*pg 71 Linux Programming Interface.*/
    int openFlags = O_CREAT | O_WRONLY | O_TRUNC; /*Flags = create file if doesnt exist, write only, destroy data in file if already exists*/
    mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw- */

    int outFiled = open(filename, openFlags, filePerms);

    struct packet packet;
    struct packet *packetP = &packet;

    /*read data from socket, output to file*/
    do
    {
        read(clientfd, packetP, sizeof(struct packet));
        write(outFiled, packet.data, packet.size);
    } while (packet.size == 1024);
    

    close(clientfd);
    close(serverfd);
    close(outFiled);
}