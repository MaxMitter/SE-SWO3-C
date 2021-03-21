#include "draw_application.h"
#include <iostream>
#include <cmath>

double Calculate(double x1, double y1, double x2, double y2) {
	double px = x2 - x1;
	double py = y2 - y1;

	double sx = px;
	double sy = 0;

	double c = px * sx + py * sy;
	double n = sqrt(pow(px, 2) + pow(py, 2)) * sqrt(pow(sx, 2) + pow(sy, 2));

	double coz = c / n;
	double angle = acos(coz);
	return angle;
}


int main(int argc, char* argv[]) {
	std::cout << Calculate(1, 1, 2, 2) << std::endl;
	
	//draw_application {}.run(argc, argv);
}