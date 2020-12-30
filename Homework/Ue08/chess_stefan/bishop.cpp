#include "bishop.h"


bishop::bishop (color c, int row, int col)
	: chessman {(c == color::white) ? ('B') : ('b'),
				 c,
				 row, col,
				 false} {
}

bool bishop::can_move_to (chessboard & cb, position & pos) const  {

	return check_line (cb, position{1, 1}, pos)
		|| check_line (cb, position{-1, -1}, pos)
		|| check_line (cb, position{-1, 1}, pos)
		|| check_line (cb, position{1, -1}, pos);
}