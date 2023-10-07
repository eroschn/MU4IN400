//
// Created by Eros Chan on 17/09/2023.
//

#include "Point.h"
#include <iostream>
#include <cstdio>

// *a en paramètre : fournir une adresse
// *a en affectation : valeur de l'adresse
// &a en appel : l'adresse
void swap_c(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

// l'utilisation de &a en paramètre permet d'éviter la
// manipulation des * dans le code, c'est spécifique à C++
// avec cette écriture, plus de manipulation d'adresses comme en C
void swap_cpp(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;
}

int main() {
  /*int a = 5, b = 10;

  std::cout << "a=" << a << " et b=" << b << std::endl;
  // swap_c(&a, &b);
  swap_cpp(a, b);
  std::cout << "a=" << a << " et b=" << b << std::endl;*/

  double x, y;
  std::cin >> x >> y;
  Point p1 (x,y);
  double d = p1.distOri();
  std::cout << "Distance :" << d << std::endl;

  return 0;
}
