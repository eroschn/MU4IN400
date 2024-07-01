#include "Banque.h"
#include <ostream>

using namespace std;

const int NB_THREAD = 10;

int main() {
  pr::Banque banque(100, 1000000);

  vector<thread> threads;

  for (int k = 0; k < 1000; k++) {
    size_t i = (size_t) rand() * banque.size(); // compte i
    size_t j = (size_t) rand() * banque.size(); // compte j
    size_t m = ((size_t) rand() * 100) + 1; // compte m

    banque.transfert(i, j, m);

    std::this_thread::sleep_for(std::chrono::milliseconds((random() * 20) + 1));
  }


  for (auto &t: threads) {
    t.join();
  }

  // TODO : tester solde = NB_THREAD * JP
  return 0;
}
