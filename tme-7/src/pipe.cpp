#include <iostream>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: /" << argv[0] << " prog1 | prog2";
    exit(0);
  }

  int i;
  int pipeIndex = 0;

  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], "|") == 0) {
      pipeIndex = i;
      break;
    };
  }

  // Checking if pipe symbol has been found
  if (pipeIndex == 0) {
    std::cerr << "Unable to find pipe symbol in arguments!" << std::endl;
    exit(1);
  }

  // std::cout << pipeIndex << std::endl;

  // pid_t f1, f2;ar

  int fd[2];
  pipe(fd);

  // fork();

  // close(fd[1]);               // on ferme la lecture
  // dup2(fd[1], STDOUT_FILENO); // redirige l'écriture vers l'écriture standard

  std::cout << argv[0] << std::endl;
  std::cout << argv[1] << std::endl;
  std::cout << argv[2] << std::endl;

  // Construct const
  int numArgs = pipeIndex - 1;
  const char* argumentsProg1[numArgs+1];

  for (i = 0; i < numArgs; i++) {
    argumentsProg1[i - 1] = argv[i];
  }
  argumentsProg1[numArgs + 1] = nullptr;

  
  
      // execv(argv[0], argv);

      // close(fd[0]);               // on ferme l'écriture
      // dup2(fd[1], STDIN_FILENO);  // redirige la lecture vers l'entrée
      // standard

      std::cout
      << argv[0];
  std::cout << argv[pipeIndex + 1];
  // execv(argv[0], argv + i);

  close(fd[0]);
  close(fd[1]);
}