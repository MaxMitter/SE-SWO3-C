#include <iostream>
#include "square.h"

square::square() {
	this->status = state::none;
	this->figure = nullptr;
}

square::~square() {
	if (this->figure != nullptr)
		delete this->figure;
}

void square::print(position pos) {
	switch (this->status) {
		case selected:
			std::cout << "(";
			break;
		case valid_dest:
			std::cout << "[";
			break;
	default:
		std::cout << (((pos.row + pos.col) % 2 == 0) ? ("°") : (" "));
		break;
	}

	if (this->figure != nullptr)
		std::cout << this->figure->get_figure();
	else
		std::cout << (((pos.row + pos.col) % 2 == 0) ? ("°") : (" "));

	switch (this->status) {
		case selected:
			std::cout << ")";
			break;
		case valid_dest:
			std::cout << "]";
			break;
	default:
		std::cout << (((pos.row + pos.col) % 2 == 0) ? ("°") : (" "));
		break;
	}
}