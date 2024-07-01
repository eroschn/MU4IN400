#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

#include <cstdlib>
#include <mutex>

namespace pr {

// MT safe version of the Queue, non blocking.
  template<typename T>
  class Queue {
    T **tab;
    const size_t allocsize;
    size_t begin;
    size_t sz;
    mutable std::mutex m;
    std::condition_variable cond;
    bool isBlocking;

    // fonctions private, sans protection mutex
    bool empty() const {
      return sz == 0;
    }

    bool full() const {
      return sz == allocsize;
    }

    void setBlocking(bool isBlocking) {
      std::unique_lock<std::mutex> lg(m);
      this->isBlocking = isBlocking;
      cond.notify_all();
    }

  public:
    Queue(size_t size) : allocsize(size), begin(0), sz(0) {
      tab = new T *[size];
      memset(tab, 0, size * sizeof(T *));
    }

    // Renvoie la taille du remplissage actuel
    size_t size() const {
      std::unique_lock <std::mutex> lg(m);
      return sz;
    }

    // Extrait le prochain élément du buffer
    T *pop() {
      std::unique_lock <std::mutex> lg(m);
      while (empty() && isBlocking) {
        cond.wait(lg);
      }
      if (full()) {
        cond.notify_all();
      }
      if (empty() && isBlocking) {
        return nullptr;
      }
      auto ret = tab[begin];
      tab[begin] = nullptr;
      sz--;
      begin = (begin + 1) % allocsize;
      return ret;
    }

    // Insère un élément dans le buffer
    bool push(T *elt) {
      std::unique_lock <std::mutex> lg(m);
      while (full()) {
        cond.wait(lg);
      }
      if (empty()) {
        cond.notify_all();
      }
      if (full()) {
        return false;
      }
      tab[(begin + sz) % allocsize] = elt;
      sz++;
      return true;
    }

    ~Queue() {
      // ?? lock a priori inutile, ne pas detruire si on travaille encore avec
      for (size_t i = 0; i < sz; i++) {
        auto ind = (begin + i) % allocsize;
        delete tab[ind];
      }
      delete[] tab;
    }
  };

}

#endif /* SRC_QUEUE_H_ */