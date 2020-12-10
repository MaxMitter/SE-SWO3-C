#include "rational.h"
#include <iostream>

rational::rational(int num, int denom) : m_num{ num }, m_denom{ denom } {
}

void rational::print(std::ostream& os) {
	os << m_num << "/" << m_denom;
}

void rational::add(const rational& other) {
	this->m_num = this->m_num * other.m_denom + this->m_denom * other.m_num;
	this->m_denom = this->m_denom * other.m_denom;
}

void rational::sub(const rational& other) {
	this->m_num = this->m_num * other.m_denom - this->m_denom * other.m_num;
	this->m_denom = this->m_denom * other.m_denom;
}

rational rational::operator+(const rational& other) const {
	rational sum = *this;
	sum.add(other);
	return sum;
}