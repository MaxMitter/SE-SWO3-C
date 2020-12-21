#pragma once

#include "./measurement.h"

#include <string>
#include <vector>

class actor : public object {
public:
	~actor();

protected:
	explicit actor(const std::string &name);   // abstract class

private:
};
