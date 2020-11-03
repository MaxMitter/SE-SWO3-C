/*weight.c:*/

#include "weight.h" /*own header*/
#include "geo.h"

double Weight(double a, double b, double c, double d) {
  return Volume(a, b, c) * d;
} /*Weight*/
