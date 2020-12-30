#include "king.h"


king::king (color c, int row, int col)
	: chessman {(c == color::white) ? ('K') : ('k'),
				 c,
				 row, col,
				 true} {
}

bool king::can_move_to (chessboard & cb, position & dest) const {
	position base = get_pos();

	// 8 possible positions
	return (move_or_capture_not_threatened(cb, base.move_by( 0,  1), dest) && dest == base.move_by( 0,  1))
		|| (move_or_capture_not_threatened(cb, base.move_by( 1,  0), dest) && dest == base.move_by( 1,  0))
		|| (move_or_capture_not_threatened(cb, base.move_by( 0, -1), dest) && dest == base.move_by( 0, -1))
		|| (move_or_capture_not_threatened(cb, base.move_by(-1,  0), dest) && dest == base.move_by(-1,  0))
		|| (move_or_capture_not_threatened(cb, base.move_by( 1,  1), dest) && dest == base.move_by( 1,  1))
		|| (move_or_capture_not_threatened(cb, base.move_by(-1, -1), dest) && dest == base.move_by(-1, -1))
		|| (move_or_capture_not_threatened(cb, base.move_by( 1, -1), dest) && dest == base.move_by( 1, -1))
		|| (move_or_capture_not_threatened(cb, base.move_by(-1,  1), dest) && dest == base.move_by(-1,  1));
}