#include "pawn.h"



bool pawn::can_move(gameboard& gb, position delta) {
	return ((delta.row == 0 || delta.row == 1) && (delta.col == 0 || delta.col == 1));
}