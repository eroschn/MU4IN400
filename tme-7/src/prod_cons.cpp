#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <vector>


using namespace pr;

void producteur(Stack<char> *stack) {
  char c;
  while (std::cin.get(c)) {
    stack->push(c);
  }
}

void consomateur(Stack<char> *stack) {
  while (true) {
    char c = stack->pop();
    std::cout << c << std::flush;
  }
}

int main() {
  shm_unlink("/okayokay");
  int fd = shm_open("/okayokay", (O_RDWR | O_CREAT | O_EXCL));
  if (fd < 0) {
    perror("Error: Unable to open file descriptor of shared memory.");
    exit(-1);
  }

  int r = ftruncate(fd, sizeof(Stack<char>));
  if (r < 0) {
    perror("Error: Unable to ftruncate.");
    shm_unlink("/okayokay");
    exit(-1);
  }

  void *ptr = mmap(NULL, sizeof(Stack<char>), (PROT_READ | PROT_WRITE), (MAP_SHARED), fd, 0);
  if (ptr == MAP_FAILED) {
    perror("Error: Unable to allocate necessary.");
    shm_unlink("/okayokay");
    exit(-1);
  }

  Stack<char> *s = new(ptr) Stack<char>(); // new (ptr) pour faire le lien

  pid_t pp = fork();
  if (pp == 0) {
    producteur(s);
    return 0;
  }

  pid_t pc = fork();
  if (pc == 0) {
    consomateur(s);
    return 0;
  }

  wait(0);
  wait(0);

  // delete s;
  shm_unlink("/okayokay");
  s->~Stack();
  munmap(ptr, sizeof(Stack<char>));

  return 0;
}

