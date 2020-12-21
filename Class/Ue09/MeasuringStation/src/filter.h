#pragma once

#include "./actor.h"
#include "./sensor.h"

class filter {
public:
	~filter();

protected:
	explicit filter(const std::string &name);                   // abstract class
	explicit filter(const std::string &name, station &station); // abstract class
};
