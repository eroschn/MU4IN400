//
// Created by Eros Chan on 06/11/2023.
//

#include "ResultatCalcul.h"
#include <vector>
#include <thread>
#include <iostream>

#define N 100
#define K 10 // Hypothèse : K < N ET N multiple de K

using std::vector;
using std::thread;

// Chaque esclave doit traiter N/K tâches
void slave(int indice, vector<ResultatCalcul> & vec) {
  int start = indice * (N/K);
  int end = start + (N/K);
  for (int i = start; i < end; i++) {
    vec[i].setResult("slave" + std::to_string(indice));
  }
}

int main() {
  vector<ResultatCalcul> results(N);
  vector<thread> threads;
  threads.reserve(K);

  for (int i = 0; i < K; i++) {
    threads.emplace_back(slave, i, std::ref(results));
  }

  for (ResultatCalcul res : results) {
    std::cout << res.getResult() << std::endl;
  }

  for (auto & t: threads) {
    t.join();
  }
}