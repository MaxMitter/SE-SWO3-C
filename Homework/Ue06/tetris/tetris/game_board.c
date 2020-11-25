#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include "game_board.h"

bool gb_is_valid_position(const position pos) {
	if (!(pos.x >= 0 && pos.x < GB_COLS &&
		  pos.y >= 0 && pos.y < GB_ROWS)) {
		return false;
	}

	//TODO check collision with block on gameboard
	for (size_t i = 0; i < block_count; i++) {
		if (blocks[i].pos.x == pos.x &&
			blocks[i].pos.y == pos.y)
			return false;
	}

	return true;
}

void gb_add_block(const block block) {
	assert(gb_is_valid_position(block.pos));
	assert(block_count < MAX_BLOCKS_COUNT);
	blocks[block_count] = block;
	block_count++;
}

void gb_render(void) {
	for (size_t i = 0; i < block_count; i++) {
		render_block(blocks[i]);
	}
}