//
// Created by Eros Chan on 06/11/2023.
//

#include "ResultatCalcul.h"
#include <vector>
#include <thread>
#include <iostream>

#define N 10

using std::vector;
using std::thread;

void slave(int indice, ResultatCalcul resultatCalcul) {
  resultatCalcul.setResult("slave" + std::to_string(indice));
}

int main() {
  vector<ResultatCalcul> results(N);
  vector<thread> threads;
  threads.reserve(N);

  for (int i = 0; i < N; i++) {
    threads.emplace_back(slave, i, std::ref(results[i]));
  }

  for (int i = 0; i < N; i++) {
    std::cout << results[i].getResult() << std::endl;
  }

  for (auto & t: threads) {
    t.join();
  }
}