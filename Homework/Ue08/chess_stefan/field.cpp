#include <iostream>

#include "field.h"

field::field () 
	: m_action{action::none} 
	, m_p_figure{nullptr} {
}

// deletion of field also deletes linkes figure
field::~field () {
	if (m_p_figure != nullptr) {
		delete m_p_figure;
	} // if
}

void field::set_reference (chessman * figure) {
	m_p_figure = figure;
}

// prints individual chessboard field
// brackets depending on action of field
void field::print(int row, int col) const {
	switch (m_action) {
		case selected:
			std::cout << "(";
			break;
		case valid_destination:
			std::cout << "[";
			break;
		default:
			std::cout << (((row + col) % 2 == 0) ?
						  ("°") : (" "));
	} // switch

	// if figure on field, print his name
	if (m_p_figure != nullptr) {
		std::cout << m_p_figure->get_name();
	} else {
		std::cout << (((row + col) % 2 == 0) ?
			("°") : (" "));
	} // if

	switch (m_action) {
		case selected:
			std::cout << ")";
			break;
		case valid_destination:
			std::cout << "]";
			break;
		default:
			std::cout << (((row + col) % 2 == 0) ?
						  ("°") : (" "));
	} // switch
}