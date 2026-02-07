#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define packsize 1024
#define errorsocket -1

int checklogic(int exp, const char *msg);

int main(int argc, char *argv[]){

  if (argc != 2 ){
    return EXIT_FAILURE;
  }

  int myport = atoi(argv[1]);
  int udpsock;
  struct sockaddr_in resource ;
  struct sockaddr_in destination = {.sin_family = AF_INET, 
                                    .sin_addr.s_addr = INADDR_ANY, 
                                    .sin_port = htons(myport)};

  char packet[packsize];

  if ((udpsock = socket(AF_INET, SOCK_DGRAM, 0)) <= 0){
    perror("SOCKET CANT BE OPENED");
    return EXIT_FAILURE;
  }

  //bindining
  int result = bind(udpsock, (struct sockaddr*)&destination, sizeof(destination));
  checklogic(result, "CANT BIND  :(");

  socklen_t addlen = sizeof(resource);
  int receivedbyte =  recvfrom(udpsock, packet, packsize, 0, (struct sockaddr *)&resource, &addlen);
  checklogic(receivedbyte, "FAILED TO RECEIVE");

  printf("packet from %s:%d, message : %s\n", inet_ntoa(resource.sin_addr), ntohl(resource.sin_port), packet);

  close (udpsock);

  return EXIT_SUCCESS;
}

int checklogic(int exp, const char *msg){
  if (exp == errorsocket){
    perror(msg);
    exit(EXIT_FAILURE);
  }

  return exp;
}
