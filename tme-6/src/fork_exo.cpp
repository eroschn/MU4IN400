#include <iostream>
#include <unistd.h>
#include <math.h>

int main() {
  const int N = 3;
  int ok = 0;
  std::cout << "main pid=" << getpid() << std::endl;

  for (int i = 1, j = N; i <= N && j == N && fork() == 0; i++) {
    std::cout << " i:j " << i << ":" << j << std::endl;

    for (int k = 1; k <= i && j == N; k++) {
      if (fork() == 0) {
        j = 0;
        std::cout << " k:j " << k << ":" << j << std::endl;
        ok++; /* You are not expected to understand this */
      }
    }
  }

  // std::cout << "ok=" << ok << std::endl;

  // Should wait min(j,N) times
  for (int i = 1; i < ok; i++) {
    //wait(0);

    if (wait(0) == -1) {
      std::cout << "J'ai trop attendu 🫨" << std::endl;
    }

    if (wait(0) != -1) {
      std::cout << "J'ai pas assez attendu 🥱" << std::endl;
    }
  }


  return 0;
}
