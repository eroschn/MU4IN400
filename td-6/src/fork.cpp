//
// Created by Eros Chan on 05/11/2023.
//

#include <unistd.h>
#include <iostream>

#define N 10

int main(int argc, char *argv[]) {

  // Création de N processus fils en parallèle
  std::cout << "Création de N processus fils en parallèle" << std::endl;

  for (int i = 0; i < N; i++) {
    if (fork() == 0) {
      std::cout << "(création) pid=" << getpid() << ", ppid=" << getppid() << ", process n°" << i << std::endl;
      exit(i);
    }
  }

  // Attente de la terminaison des N processus fils
  for (int i = 0; i < N; i++) {
    int status;
    pid_t pid = wait(&status); // &status : for exit status
    //pid_t pid = waitpid(-1, &status, 0); // -1 : for any child process, &status : for exit status, 0 : for options
    std::cout << "(mort) pid=" << pid << ", process n°" << WEXITSTATUS(status) << std::endl;
  }

  std::cout << "Attente de la terminaison des N processus fils" << std::endl;
}