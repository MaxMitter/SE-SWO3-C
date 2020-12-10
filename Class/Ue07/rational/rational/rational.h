#pragma once
#include <iostream>

class rational {

public:
	rational(int num=0, int denom=1);
	void print(std::ostream &os = std::cout);
	void add(const rational& other);
	void sub(const rational& other);

	rational operator+(const rational& other) const;

private:
	int m_num;
	int m_denom;
};