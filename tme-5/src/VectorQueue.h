//
// Created by Eros Chan on 31/10/2023.
//

#pragma_once SRC_QUEUE_H

#include <vector>
#include <string>

namespace pr {

  template<typename T>
  class Queue {
    std::vector<T *> vector; // Vecteur de T*
    const size_t allocsize; // Taille du vecteur
    size_t sz; // Remplissage actuel

  public:
    Queue(size_t size) : vector(size), allocsize(size), size(0) {}

    // Renvoie la taille du remplissage actuel
    size_t size() {
      return sz;
    }

    // Extrait le prochain élément du buffer
    T *pop() {
      std::iterator end = vector.end();
      T *nextElement = vector.at(end)
      vector.erase(end);
      sz--;
      return nextElement;
    }

    // Insère un élément dans le buffer
    void push(T *t) {
      vector.push_back(t);
      sz++;
    }
  };
