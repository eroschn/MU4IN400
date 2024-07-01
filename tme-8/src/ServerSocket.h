#ifndef SRC_SERVERSOCKET_H_
#define SRC_SERVERSOCKET_H_

#include "Socket.h"
#include "iostream"
#include "ostream"

namespace pr {

  class ServerSocket {
    int socketfd;

  public :

    ServerSocket(int port) {
      int serverfd;
      sockaddr_in sin;

      // The serverfd descriptor returned by socket is only partially opened and cannot yet be used for reading and
      // writing
      serverfd = socket(AF_INET, SOCK_STREAM, 0);

      // On vérifie si le description de socket a bien été ouvert
      if (serverfd == -1) {
        perror("Erreur : Impossible d'ouvrir le description de socket !");
        exit(-1);
      }

      sin.sin_family = AF_INET;                 // Address family (always AF_INET)
      sin.sin_port = htons(port);               // Port number in network byte order
      sin.sin_addr.s_addr = htonl(INADDR_ANY);  // IP address in network byte order (INADDR_ANY = 0.0.0.0)

      if (bind(serverfd, (struct sockaddr *) &sin, sizeof sin)) {
        ::close(serverfd);
      }

      // Taille de liste d'attente
      listen(serverfd, 50);
      socketfd = serverfd;
    }

    int getFD() { return socketfd; }

    bool isOpen() const { return socketfd != -1; }

    Socket accept() {
      int clientfd;
      sockaddr addr;
      socklen_t len;

      clientfd = ::accept(socketfd, 0, 0);
      len = sizeof addr;

      if ((clientfd = ::accept(socketfd, &addr, &len)))
      {}

      std::cout << "Connexion de " << addr << std::endl;
      return clientfd;
    }

    void close();
  };

} // ns pr
#endif /* SRC_SERVERSOCKET_H_ */
