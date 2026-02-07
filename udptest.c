#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  if (argc != 4){
    return EXIT_FAILURE;
  }

  // main var
  const char *ip = argv[1];
  int port = atoi(argv[2]);
  const char *message = argv[3];

  // string ip to 
  struct sockaddr_in desti = {.sin_family = AF_INET, .sin_port = htons(port)};

  if (inet_pton(AF_INET, ip, &(desti.sin_addr)) <= 0){
    perror("something wrong with ip");
    return EXIT_FAILURE;
  }

  int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
}
