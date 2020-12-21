#pragma once

#include "./object.h"

#include <string>
#include <vector>

class sensor : public object {

public:
	~sensor();

protected:
	explicit sensor(const std::string &name);
	explicit sensor(const std::string &name, station &station);

private:
};
