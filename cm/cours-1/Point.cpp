//
// Created by Eros Chan on 17/09/2023.
//

#include "Point.h"
#include <cmath>

Point::Point(double x, double y) {
  this->x = x;
  this->y = y;
}

double Point::distOri() {
  return sqrt(this->x * this->x + this->y * this->y);
}