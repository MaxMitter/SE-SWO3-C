#include "position.h"


position::position (int row, int col) 
	: row{row}
	, col{col} {
}

position::position (const position & cpy)
	: row{cpy.row}
	, col{cpy.col} {
}

// adds rows/cols to pos and returns temporary object
// only use for input parameters by value (to create a copy)!
// does not alter object
position & position::move_by (int drow, int dcol) {
	static position temp{};
	temp.row = row + drow;
	temp.col = col + dcol;
	return temp;
}

// swaps two positions' data components
void position::swap (position & other) {
	position temp{other.row, other.col};
	other.row = row; other.col = col;
	row = temp.row; col = temp.col;
}