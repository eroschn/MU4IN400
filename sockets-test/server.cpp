#include <iomanip>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <unistd.h>

void echo(int connfd) {
  size_t n;
  char buf[1024];
  rio_t rio;

  rio_
}

int main(int argc, char **argv) {

  int listenfd, connfd, port, clientlen;

  struct sockaddr_in clientaddr;
  struct hostent *hp;

  char *haddrp;

  if (argc != 2) {
    std::cerr << "Usage: ./" << argv[0] << " <port>" << std::endl;
    exit(0);
  }

  port = atoi(argv[1]);

  // Create socket descriptor
  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0) < 0)) {
    perror("Error: Unable to create socket connection\n");
    exit(0);
  }

  // Create endpoint
  struct sockaddr_in serveraddr;
  memset((char *)&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons((unsigned short)port);
  if (bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
    perror("Error: Unable to bind\n");
    exit(0);
  }

  // Accept connection requests
  if (listen(listenfd, 5) < 0) { // 5 = nb connexions pendantes maximum
    perror("Error: Unable to accept connection requests\n");
    exit(0);
  }

  while (true) {
    connfd =
        accept(listenfd, (struct sockaddr *)&clientaddr.sin_addr, &clientlen);
    std::cout << "connfd=" << connfd << std::endl;
    close(connfd);
  }
}
