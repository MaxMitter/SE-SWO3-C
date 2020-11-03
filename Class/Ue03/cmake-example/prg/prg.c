/*prg.c:*/

#include <stdio.h>

#include "geo.h"
#include "weight.h"

int main() {
	double a = 1.0;
	double b = 2.0;
	double c = 3.0;
	double d = 4.0;
 
	printf("Area =   %f\n", Area(a, b));
	printf("Volume = %f\n", Volume(a, b, c));
	printf("Weight = %f\n", Weight(a, b, c, d));

  d = 15;
  printf("%f\n", d);
	return 0;
} /*main*/
