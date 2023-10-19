//
// Created by Eros Chan on 12/10/2023.
//

#ifndef MU4IN400_ITERATOR_H
#define MU4IN400_ITERATOR_H

#include <ostream>

template <typename iterator>
size_t count(iterator begin, iterator end) {
  size_t count = 0;

  while (begin != end) {
    count++;
    begin++;
  }

  return count;
}

template <typename iterator, typename T>
size_t count_if_equal(iterator begin, iterator end, const T& val) {
  size_t count = 0;

  while (begin != end) {
    if (*begin == val) count++;
    begin++;
  }
  return count;
}

#endif //MU4IN400_ITERATOR_H