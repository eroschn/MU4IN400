#ifndef SRC_SOCKET_H_
#define SRC_SOCKET_H_

#include <netinet/ip.h>
#include <string>
#include <iosfwd>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <ostream>

namespace pr {

  class Socket {
    int fd;

  public :
    Socket() : fd(-1) {}

    Socket(int fd) : fd(fd) {}

    void connect(const std::string &host, int port) {
      int clientfd;
      addrinfo *res;
      in_addr ipv4;

      clientfd = socket(AF_INET, SOCK_STREAM, 0);

      if (clientfd == -1) {
        perror("Erreur : Impossible d'ouvrir le descripteur de socket !");
        exit(-1);
      }

      getaddrinfo(host.c_str(), std::to_string(port), nullptr, &res);
      ipv4 = ((struct sockaddr_in *) res)->sin_addr;

      connect(ipv4, port);
    }

    void connect(in_addr ipv4, int port) {
      int clientfd;
      sockaddr_in serveraddr;

      serveraddr.sin_family = AF_INET;   // Address family (always AF_INET)
      serveraddr.sin_port = htons(port); // Port number in network byte order
      serveraddr.sin_addr = ipv4;        // IP address in network byte order

      clientfd = socket(AF_INET, SOCK_STREAM, 0);

      if (clientfd == -1) {
        perror("Erreur : Impossible d'ouvrir le descripteur de socket !");
        exit(-1);
      }

      if (::connect(clientfd, (struct sockaddr *) &serveraddr, sizeof serveraddr) == -1) {
        ::close(clientfd);
        perror("Erreur : Impossible d'initier la connexion !");
        exit(-1);
      }
    }

    bool isOpen() const { return fd != -1; }

    int getFD() { return fd; }

    void close();
  };

  std::ostream &operator<<(std::ostream &os, struct sockaddr_in *addr) {
    char hname[1024];

    if (getnameinfo((struct sockaddr *) addr, sizeof *addr, hname, sizeof hname, nullptr, 0, 0)) {
      os << hname;
    }
    return os;
  }

}

#endif /* SRC_SOCKET_H_ */
