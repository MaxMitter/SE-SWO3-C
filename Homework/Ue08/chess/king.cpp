#include "king.h"
#include "gameboard.h"

#define MAX_MOVABLE_POS 8

bool king::can_move(gameboard &board, position new_pos) {
	position old_pos = this->get_position();

	bool can_move = false;

	can_move = move(board, old_pos.add(-1, -1)) && new_pos == old_pos.add(-1, -1);
	can_move = move(board, old_pos.add(-1, 0)) && new_pos == old_pos.add(-1, 0);
	can_move = move(board, old_pos.add(-1, 1)) && new_pos == old_pos.add(-1, 1);
	can_move = move(board, old_pos.add(0, -1)) && new_pos == old_pos.add(0, -1);
	can_move = move(board, old_pos.add(0, 1)) && new_pos == old_pos.add(0, 1);
	can_move = move(board, old_pos.add(1, -1)) && new_pos == old_pos.add(1, -1);
	can_move = move(board, old_pos.add(1, 0)) && new_pos == old_pos.add(1, 0);
	can_move = move(board, old_pos.add(1, 1)) && new_pos == old_pos.add(1, 1);

	//board.debug("board");

	return can_move;
}