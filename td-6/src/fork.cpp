//
// Created by Eros Chan on 05/11/2023.
//

#include <unistd.h>
#include <iostream>

#define N 10

int main(int argc, char *argv[]) {

  // Création de N processus fils en parallèle
  for (int i = 0; i < N; i++) {

    if (fork() == 0) {
      std::cout << "pid=" << getpid() << ", ppid=" << getppid() << ", process n°" << i << std::endl;
      exit(0);
    }

  }

  // Attente la terminaison des N processus fils
  for (int i = 0; i < N; i++) {
    wait(nullptr);
  }

  std::cout << "j'ai attendu mes enfants !" << std::endl;
}