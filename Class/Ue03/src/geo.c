/*geo.c:*/

#include "geo.h" /*own header*/

double Area(double a, double b) {
  return a * b ;
} /*Area*/

double Volume(double a, double b, double c) {
  return Area(a, b) * c;
} /*Volume*/