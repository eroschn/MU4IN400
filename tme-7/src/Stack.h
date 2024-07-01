#pragma once

#include <cstring> // size_t,memset
#include <semaphore.h>

namespace pr {

#define STACKSIZE 100

  template<typename T>
  class Stack {
    T tab[STACKSIZE];
    size_t sz;
    sem_t mutex, s_vide, s_plein;

  public :
    Stack() : sz(0) {
      memset(tab, 0, sizeof tab);
      sem_init(&mutex, 1, 1);
      sem_init(&s_vide, 1, STACKSIZE);
      sem_init(&s_plein, 1, 0);
    }

    T pop() {
      sem_wait(&s_vide);
      sem_wait(&mutex);
      T toret = tab[--sz];
      sem_post(&mutex);
      sem_post(&s_vide);
      return toret;
    }

    void push(T elt) {
      sem_wait(&s_plein);
      sem_wait(&mutex);
      tab[sz++] = elt;
      sem_post(&mutex);
      sem_post(&s_plein);
    }

    ~Stack() {
      sem_destroy(&mutex);
      sem_destroy(&s_vide);
      sem_destroy(&s_plein);
    }
  };

}
