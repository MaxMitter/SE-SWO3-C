#include "./station.h"

#include <iostream>

station::station(const std::string &name) {
	cout_station() << "got constructed.\n";
}

station::~station() {
	cout_station() << "got deconstructed.\n";
}
