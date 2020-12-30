#include "knight.h"


knight::knight (color c, int row, int col)
	: chessman {(c == color::white) ? ('N') : ('n'),
				 c,
				 row, col,
				 false} {
}

bool knight::can_move_to (chessboard & cb, position & dest) const {
	position base = get_pos();
	
	// 8 possible positions
	return (move_or_capture(cb, base.move_by(-1, -2)) && dest == base.move_by(-1, -2))
		|| (move_or_capture(cb, base.move_by( 1,  2)) && dest == base.move_by( 1,  2))
		|| (move_or_capture(cb, base.move_by( 1, -2)) && dest == base.move_by( 1, -2))
		|| (move_or_capture(cb, base.move_by(-1,  2)) && dest == base.move_by(-1,  2))
		|| (move_or_capture(cb, base.move_by(-2, -1)) && dest == base.move_by(-2, -1))
		|| (move_or_capture(cb, base.move_by( 2,  1)) && dest == base.move_by( 2,  1))
		|| (move_or_capture(cb, base.move_by( 2, -1)) && dest == base.move_by( 2, -1))
		|| (move_or_capture(cb, base.move_by(-2,  1)) && dest == base.move_by(-2,  1));
}