#pragma once

#include <cstdlib>
#include <mutex>

namespace pr {

  class Barrier {
    mutable std::mutex m;
    std::condition_variable cond;
    int cpt;
    const int goal;

  public:

    Barrier(int N) : goal(N) {}

    void done() {
      std::unique_lock<std::mutex> lg(m);
      cpt++;
      // notifie la condition sur goal atteint
      if (cpt == goal) cond.notify_all();
    }

    void waitFor() {
      std::unique_lock<std::mutex> lg(m);
      cond.wait(lg, [&]() { return cpt == goal; });
    }
  };

}
