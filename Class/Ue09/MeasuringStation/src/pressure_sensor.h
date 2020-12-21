#pragma once

#include "./sensor.h"

class pressure_sensor {

public:
	explicit pressure_sensor(const std::string &name, station &station);
};
