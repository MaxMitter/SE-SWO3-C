#pragma once

#include "./sensor.h"
#include "./station.h"

class temperature_sensor {

public:
	explicit temperature_sensor(const std::string &name, station &station);
};
