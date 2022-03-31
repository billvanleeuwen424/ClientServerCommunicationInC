
#include "common.c"
#include <libgen.h>

int main(int argc, char *argv[]){



    /*exit if incorrect params*/
    if(argc != 2){
        printf("Enter only the filename.\n");
        printf("./client [filename]\n");
        exit(-1);
    }

    int inFiled;
    
    if((inFiled = open(argv[1], O_RDONLY)) < 0){
        fprintf(stderr, "Error Opening File. %s\n", strerror(errno));
        exit(-1);
    }


    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(57505); //50000 + last 4 of student num
    server.sin_addr.s_addr = inet_addr("192.168.0.190");


    /*create socket, connect*/
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(connect(clientfd, (struct sockaddr*) &server, sizeof(server)) < 0){
        fprintf(stderr, "Connection error. %s\n", strerror(errno));
        exit(-1);
    }

    struct packet packet;
    struct packet *packetP = &packet;


    /*split the filename off of any potential path passed
    write it to the server*/
    argv[1] = basename(argv[1]);

    strcat(argv[1],"\n");


   write(clientfd, argv[1], strlen(argv[1]));


    /*read the file, write to the socket*/
    int numRead;
    while ((numRead = read(inFiled, packet.data, 1024)) > 0){ //pg 71 Linux Programming Interface
        packet.size = numRead;
        write(clientfd,packetP, sizeof(packet));
    }

    close(inFiled);
    close(clientfd);
}