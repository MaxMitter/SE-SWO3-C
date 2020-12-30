#include "rook.h"


rook::rook (color c, int row, int col)
	: chessman {(c == color::white) ? ('R') : ('r'),
				 c,
				 row, col,
				 false} {

}

bool rook::can_move_to (chessboard & cb, position & dest) const {

	return check_line (cb, position{0, 1}, dest)
		|| check_line (cb, position{0, -1}, dest)
		|| check_line (cb, position{1, 0}, dest)
		|| check_line (cb, position{-1, 0}, dest);

}