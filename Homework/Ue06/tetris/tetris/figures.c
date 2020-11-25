#include "figures.h"

static figure current;

static shape random_shape(void);
static void init_shape(void);

bool fg_try_move(int dx, int dy) {
	for (int r = 0; r < FIGURE_MAX_SIZE; r++) {
		for (int c = 0; c < FIGURE_MAX_SIZE; c++) {
			if (is_block(current.blocks[r][c])) {
				if (!cb_try_move_block(current.blocks[r][c], dx, dy))
					return false;
			}
		}
	}

	for (int r = 0; r < FIGURE_MAX_SIZE; r++) {
		for (int c = 0; c < FIGURE_MAX_SIZE; c++) {
			if (is_block(current.blocks[r][c]))
				move_block(&(current.blocks[r][c]), dx, dy);
		}
	}
	return true;
}

bool fg_try_rotate_figure(void) {
	for (int r = 0; r < FIGURE_MAX_SIZE; r++) {
		for (int c = 0; c < FIGURE_MAX_SIZE; c++) {
			current.blocks[r][c] = current.blocks[c][r];

		}
	}

	return true;
}

void fg_render(void) {
	render_figure(current);
}

figure fg_new_figure(void) {
	current.figure_shape = random_shape();
	init_shape();
}

void init_i(void) {
	current.blocks[0][2] = cb_new_block_color(color_cyan);
	current.blocks[1][2] = cb_new_block_color(color_cyan);
	current.blocks[1][2].pos.y -= 1;
	current.blocks[2][2] = cb_new_block_color(color_cyan);
	current.blocks[2][2].pos.y -= 2;
	current.blocks[3][2] = cb_new_block_color(color_cyan);
	current.blocks[3][2].pos.y -= 3;
}

void init_o(void) {
	current.blocks[2][1] = cb_new_block_color(color_yellow);
	current.blocks[2][2] = cb_new_block_color(color_yellow);
	current.blocks[2][2].pos.x += 1;
	current.blocks[3][1] = cb_new_block_color(color_yellow);
	current.blocks[3][1].pos.y -= 1;
	current.blocks[3][2] = cb_new_block_color(color_yellow);
	current.blocks[3][2].pos.x += 1;
	current.blocks[3][2].pos.y -= 1;
}

void init_t(void) {
	current.blocks[2][2] = cb_new_block_color(color_magenta);
	current.blocks[3][1] = cb_new_block_color(color_magenta);
	current.blocks[3][1].pos.x -= 1;
	current.blocks[3][1].pos.y -= 1;
	current.blocks[3][2] = cb_new_block_color(color_magenta);
	current.blocks[3][2].pos.y -= 1;
	current.blocks[3][3] = cb_new_block_color(color_magenta);
	current.blocks[3][3].pos.x += 1;
	current.blocks[3][3].pos.y -= 1;
}

void init_j(void) {
	current.blocks[2][1] = cb_new_block_color(color_blue);
	current.blocks[2][2] = cb_new_block_color(color_blue);
	current.blocks[2][2].pos.y -= 1;
	current.blocks[2][3] = cb_new_block_color(color_blue);
	current.blocks[2][3].pos.y -= 2;
	current.blocks[1][3] = cb_new_block_color(color_blue);
	current.blocks[1][3].pos.x -= 1;
	current.blocks[1][3].pos.y -= 2;
}

void init_l(void) {
	current.blocks[2][1] = cb_new_block_color(color_orange);
	current.blocks[2][2] = cb_new_block_color(color_orange);
	current.blocks[2][2].pos.y -= 1;
	current.blocks[2][3] = cb_new_block_color(color_orange);
	current.blocks[2][3].pos.y -= 2;
	current.blocks[1][3] = cb_new_block_color(color_orange);
	current.blocks[1][3].pos.x += 1;
	current.blocks[1][3].pos.y -= 2;
}

void init_s(void) {
	current.blocks[2][2] = cb_new_block_color(color_green);
	current.blocks[2][3] = cb_new_block_color(color_green);
	current.blocks[2][3].pos.x += 1;
	current.blocks[3][2] = cb_new_block_color(color_green);
	current.blocks[3][2].pos.y -= 1;
	current.blocks[3][1] = cb_new_block_color(color_green);
	current.blocks[3][1].pos.x -= 1;
	current.blocks[3][1].pos.y -= 1;
}

void init_z(void) {
	current.blocks[2][0] = cb_new_block_color(color_green);
	current.blocks[2][0].pos.x -= 1;
	current.blocks[2][1] = cb_new_block_color(color_green);
	current.blocks[3][1] = cb_new_block_color(color_green);
	current.blocks[3][1].pos.y -= 1;
	current.blocks[3][2] = cb_new_block_color(color_green);
	current.blocks[3][1].pos.x += 1;
	current.blocks[3][2].pos.y -= 1;
	
}

void reset_blocks(void) {
	for (int r = 0; r < FIGURE_MAX_SIZE; r++) {
		for (int c = 0; c < FIGURE_MAX_SIZE; c++) {
			current.blocks[r][c].pos.x = -1;
			current.blocks[r][c].pos.y = -1;
		}
	}
}

void init_shape(void) {

	reset_blocks();

	switch (current.figure_shape) {
		case I:
			init_i();
			break;
		case O:
			init_o();
			break;
		case T:
			init_t();
			break;
		case J:
			init_j();
			break;
		case L:
			init_l();
			break;
		case S:
			init_s();
			break;
		case Z:
			init_z();
			break;
	}
}

bool is_block(block bl) {
	return (bl.pos.x != -1) || (bl.pos.y != -1);
}

figure fg_get_current(void) {
	return current;
}

static shape random_shape(void) {
	static shape shapes[] = {
		I, O, T, J, L, S, Z
	};

	int n_shapes = sizeof(shapes) / sizeof(shapes[0]);

	return shapes[rand() % n_shapes];
}