#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "game_board.h"

static int score = 0;
static double timer_interval = 0.5;

bool gb_is_valid_position(const position pos) {
	if (!(pos.x >= 0 && pos.x < GB_COLS &&
		  pos.y >= 0 && pos.y < GB_ROWS)) {
		return false;
	}

	return (blocks[pos.y][pos.x].color == color_black);
}

bool gb_is_row_full(const int row) {
	for (int i = 0; i < GB_COLS; i++) {
		if (blocks[row][i].color == color_black)
			return false;
	}

	return true;
}

static void gb_remove_row(const int row) {
	for (int i = row + 1; i < GB_ROWS; i++) {
		for (int j = 0; j < GB_COLS; j++) {
			blocks[i - 1][j] = blocks[i][j];
			blocks[i - 1][j].pos.y--;
		}
	}

	//set upmost row to black
	for (int i = 0; i < GB_COLS; i++) {
		blocks[GB_ROWS - 1][i].color = color_black;
	}

	score++;
	if (score % 5 == 0) {
		if (timer_interval >= 0.05)
			timer_interval -= 0.05;
	}
}

void gb_add_block(const block block) {
	assert(gb_is_valid_position(block.pos));
	blocks[block.pos.y][block.pos.x] = block;

	if (gb_is_row_full(block.pos.y))
		gb_remove_row(block.pos.y);
}

void gb_init_game_board(void) {
	srand(time(0));
	score = 0;
	for (int i = 0; i < GB_ROWS; i++) {
		for (int j = 0; j < GB_COLS; j++) {
			blocks[i][j].pos.x = j;
			blocks[i][j].pos.y = i;
			blocks[i][j].color = color_black;
		}
	}
}

void gb_render(void) {
	for (size_t i = 0; i < GB_ROWS; i++) {
		for (size_t j = 0; j < GB_COLS; j++) {
			render_block(blocks[i][j]);
		}
	}
}

int gb_get_score(void) {
	return score;
}

double gb_get_interval(void) {
	return timer_interval;
}

void gb_set_interval(double intvl) {
	timer_interval = intvl;
}