#include <iostream>
#include <fenv.h>
#include <netinet/in.h>
#include <sys/socket.h>

void server() {
  int listenfd;

  // Create new socket description
  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0) < 0)) {
    perror("Error: Unable de create a socket description\n");
    exit(0);
  }

  // Bind socket connection
  struct sockaddr_in serveraddress;
  serveraddress.sin_family = AF_INET;
  serveraddress.sin_addr.s_addr = htonl(INADRR_ANY);
  serveraddress.sin_port = htons((unsigned short)12345);
  if (bind(listenfd, (struct sockaddr*)&serveraddress, sizeof(serveraddress))){
    perror("Error: Unable to bind a socket connection to specified port");
    exit(0);
  }

  if (listen(listenfd, LISTENQ) < 0) {
    perror("Error: Unable to start listening to specified port\n");
    exit(0);
  }


  if (accept(listenfd, (struct sockaddr*)&serveraddress, sizeof(serveraddress))){
    
  }
int main(int argc, char **argv) { int socketfd; }
