#include "game_engine.h"
#include "current_block.h"
#include "game_board.h"
#include "figures.h"

static bool game_over = false;

bool ge_handle_move(int dx, int dy, int turn) {
	if (game_over)
		return false;

	/*if (!cb_try_move(dx, dy) && dy == -1) {
		block current = cb_get_block();
		gb_add_block(current);
		current = cb_new_block();

		if (!gb_is_valid_position(current.pos))
			game_over = true;
	}*/

	bool succesfull_move = true;

	if (turn == 1) {
		if (!fg_rotate_figure())
			succesfull_move = false;
	}
	else {
		if (!fg_try_move(dx, dy) && dy == -1)
			succesfull_move = false;
	}

	if (!succesfull_move) {
		figure current = fg_get_current();
		for (int r = 0; r < FIGURE_MAX_SIZE; r++) {
			for (int c = 0; c < FIGURE_MAX_SIZE; c++) {
				if (is_block(current.blocks[r][c]))
					gb_add_block(current.blocks[r][c]);
			}
		}

		fg_new_figure();

		if (!fg_try_move(0, 0))
			game_over = true;
	}

	return !game_over;
}

bool ge_is_game_over(void) {
	return game_over;
}