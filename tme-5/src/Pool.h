#pragma once

#include "Queue-old.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

  class Pool {
    Queue<Job> queue;
    std::vector<std::thread> threads;

  public:
    Pool(int qsize) : queue(qsize) {};

    void start(int nbthread) {
      threads.reserve(nbthread);

      for (int i = 0; i < nbthread; i++) {

        threads.emplace_back(std::thread([&] {
          while (true) {
            Job *j = queue.pop();
            if (!j) return;
            j->run();
            delete j;
          }
        }));
      }
    }

    void submit(Job *job) {
      queue.push(job);
    }

    void stop() {
      queue.setBlocking(false);
      for (auto &t: threads) {
        t.join();
      }
      threads.clear();
    }

    ~Pool() {}
  };

}
