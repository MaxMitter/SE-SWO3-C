#include <stdlib.h>
#include "current_block.h"
#include "game_board.h"

static block current = { { GB_COLS / 2, GB_ROWS - 1}, color_red };

static color random_color(void);

bool cb_try_move(int dx, int dy) {
	position pos = current.pos;
	pos.x += dx;
	pos.y += dy;
	if (!gb_is_valid_position(pos))
		return false;

	current.pos = pos;
	return true;
}

bool cb_try_move_block(block bl, int dx, int dy) {
	position pos = bl.pos;
	pos.x += dx;
	pos.y += dy;
	if (!gb_is_valid_position(pos))
		return false;

	return true;
}

void move_block(block* bl, int dx, int dy) {
	bl->pos.x += dx;
	bl->pos.y += dy;
}

void cb_render(void) {
	render_block(current);
}

block cb_new_block(void) {
	current.pos.x = GB_COLS / 2;
	current.pos.y = GB_ROWS - 1;
	current.color = random_color();

	return current;
}

block cb_new_block_color(color color) {
	current.pos.x = GB_COLS / 2;
	current.pos.y = GB_ROWS - 1;
	current.color = color;

	return current;
}

block new_block_subgrid(int sub_pos_x, int sub_pos_y) {
	current.pos.x = (GB_COLS / 2) + sub_pos_x;
	current.pos.y = (GB_ROWS - 1) + sub_pos_y;
	current.color = random_color();

	return current;
}

block cb_get_block(void) {
	return current;
}

static color random_color(void) {
	static color colors[] = {
		color_red,
		color_blue,
		color_green,
		color_white,
		color_yellow,
		color_magenta,
		color_cyan
	};

	int n_colors = sizeof(colors) / sizeof(colors[0]);

	return colors[rand() % n_colors];
}