#include "pawn.h"
#include "chessboard.h"
#include "field.h"

pawn::pawn (color c, int row, int col)
	: chessman{(c == color::white) ? ('P') : ('p'),
				 c,
				 row, col,
				 false} {
}

bool pawn::can_move_to (chessboard & cb, position & dest) const {
	
	position base = get_pos();
	int drow = (cb.get_player() == color::white) ? (-1) : (1);
	bool could_move = false;
	
	if (double_move_possible (cb) && move(cb, base.move_by(drow, 0))) {
		could_move = (move(cb, base.move_by(2 * drow, 0)) && dest == base.move_by(2 * drow, 0));
	} // if
	could_move |= (move(cb, base.move_by(drow, 0)) && dest == base.move_by(drow, 0));

	return could_move || (capture(cb, base.move_by(drow, -1)) && dest == base.move_by(drow, -1))
		|| (capture(cb, base.move_by(drow,  1)) && dest == base.move_by(drow, 1));
}

bool pawn::double_move_possible (chessboard & cb) const {
	return (get_pos().row == 1 || get_pos().row == cb.get_height() - 2);
}