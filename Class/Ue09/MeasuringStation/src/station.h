#pragma once

#include "./sensor.h"

#include <string>
#include <vector>

class station : public object {
public:
	station(const std::string &name);
	~station();

private:
	std::ostream& cout_station() const { return std::cout << "station '" << m_name << "': " };

	std::string m_name;
	std::vector<sensor*> m_sensors;
};
