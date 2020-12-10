#include "figures.h"

static figure current;

static shape random_shape(void);
static void init_shape(void);

bool fg_try_move(int dx, int dy) {
	for (int r = 0; r < FIGURE_MAX_SIZE; r++) {
		for (int c = 0; c < FIGURE_MAX_SIZE; c++) {
			if (is_block(current.blocks[r][c])) {
				if (!b_try_move_block(current.blocks[r][c], dx, dy))
					return false;
			}
		}
	}

	for (int r = 0; r < FIGURE_MAX_SIZE; r++) {
		for (int c = 0; c < FIGURE_MAX_SIZE; c++) {
			if (is_block(current.blocks[r][c]))
				b_move_block(&(current.blocks[r][c]), dx, dy);
		}
	}
	return true;
}

void fg_rotate_current(rotation new_rotation) {
	if (current.figure_shape == I) {
		for (int r = 0; r < FIGURE_MAX_SIZE; r++) {
			for (int c = 0; c < FIGURE_MAX_SIZE; c++) {
				current.blocks[r][c] = new_rotation.piece.blocks[r][c];
				int dx = c - r;
				int dy = c - r;
				if (is_block(current.blocks[r][c]))
					b_move_block(&(current.blocks[r][c]), dx, dy);
			}
		}
	}
	else {
		for (int r = 0; r < FIGURE_MAX_SIZE - 1; r++) {
			for (int c = 0; c < FIGURE_MAX_SIZE - 1; c++) {
				current.blocks[r][c] = new_rotation.piece.blocks[r][c];
			}
		}
	}
}

bool fg_try_rotate_figure(void) {

	rotation new_rotation;
	//Turning O will result in the same position as before
	if (current.figure_shape == O)
		return true;

	if (current.figure_shape == I) {
		for (int r = 0; r < FIGURE_MAX_SIZE; r++) {
			for (int c = 0; c < FIGURE_MAX_SIZE; c++) {
				if (is_block(current.blocks[c][r])) {
					new_rotation.piece.blocks[r][c] = current.blocks[c][r];
					int dx = c - r;
					int dy = c - r;
					if (!b_try_move_block(current.blocks[c][r], dx, dy))
						return false;
				}
			}
		}

		fg_rotate_current(new_rotation);
	}
	else {
		for (int r = 0; r < FIGURE_MAX_SIZE - 1; r++) {
			for (int c = 0; c < FIGURE_MAX_SIZE - 1; c++) {
				int row_relative = r - 1;
				int col_relative = c - 1;
				
				int row_translation = col_relative;
				int col_translation = -row_relative;

				new_rotation.piece.blocks[r][c] = current.blocks[1 + row_translation][1 + col_translation];

				int dx = c - (1 + col_translation);
				int dy = -(r - (1 + row_translation));

				if (is_block(new_rotation.piece.blocks[r][c])) {
					if (!b_try_move_block(new_rotation.piece.blocks[r][c], dx, dy))
						return false;
					else {
						b_move_block(&(new_rotation.piece.blocks[r][c]), dx, dy);
					}
				}
			}
		}

		fg_rotate_current(new_rotation);
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
	current.blocks[0][1] = b_new_block_color(color_cyan);
	current.blocks[1][1] = b_new_block_color(color_cyan);
	current.blocks[1][1].pos.y -= 1;
	current.blocks[2][1] = b_new_block_color(color_cyan);
	current.blocks[2][1].pos.y -= 2;
	current.blocks[3][1] = b_new_block_color(color_cyan);
	current.blocks[3][1].pos.y -= 3;
}

void init_o(void) {
	current.blocks[2][1] = b_new_block_color(color_yellow);
	current.blocks[2][2] = b_new_block_color(color_yellow);
	current.blocks[2][2].pos.x += 1;
	current.blocks[3][1] = b_new_block_color(color_yellow);
	current.blocks[3][1].pos.y -= 1;
	current.blocks[3][2] = b_new_block_color(color_yellow);
	current.blocks[3][2].pos.x += 1;
	current.blocks[3][2].pos.y -= 1;
}

void init_t(void) {
	current.blocks[0][1] = b_new_block_color(color_magenta);
	current.blocks[1][0] = b_new_block_color(color_magenta);
	current.blocks[1][0].pos.x -= 1;
	current.blocks[1][0].pos.y -= 1;
	current.blocks[1][1] = b_new_block_color(color_magenta);
	current.blocks[1][1].pos.y -= 1;
	current.blocks[1][2] = b_new_block_color(color_magenta);
	current.blocks[1][2].pos.x += 1;
	current.blocks[1][2].pos.y -= 1;
}

void init_j(void) {
	current.blocks[0][1] = b_new_block_color(color_blue);
	current.blocks[1][1] = b_new_block_color(color_blue);
	current.blocks[1][1].pos.y -= 1;
	current.blocks[2][1] = b_new_block_color(color_blue);
	current.blocks[2][1].pos.y -= 2;
	current.blocks[2][0] = b_new_block_color(color_blue);
	current.blocks[2][0].pos.x -= 1;
	current.blocks[2][0].pos.y -= 2;
}

void init_l(void) {
	current.blocks[0][1] = b_new_block_color(color_orange);
	current.blocks[1][1] = b_new_block_color(color_orange);
	current.blocks[1][1].pos.y -= 1;
	current.blocks[2][1] = b_new_block_color(color_orange);
	current.blocks[2][1].pos.y -= 2;
	current.blocks[2][2] = b_new_block_color(color_orange);
	current.blocks[2][2].pos.x += 1;
	current.blocks[2][2].pos.y -= 2;
}

void init_s(void) {
	current.blocks[0][1] = b_new_block_color(color_green);
	current.blocks[0][2] = b_new_block_color(color_green);
	current.blocks[0][2].pos.x += 1;
	current.blocks[1][1] = b_new_block_color(color_green);
	current.blocks[1][1].pos.y -= 1;
	current.blocks[1][0] = b_new_block_color(color_green);
	current.blocks[1][0].pos.x -= 1;
	current.blocks[1][0].pos.y -= 1;
}

void init_z(void) {
	current.blocks[0][0] = b_new_block_color(color_red);
	current.blocks[0][0].pos.x -= 1;
	current.blocks[0][1] = b_new_block_color(color_red);
	current.blocks[1][1] = b_new_block_color(color_red);
	current.blocks[1][1].pos.y -= 1;
	current.blocks[1][2] = b_new_block_color(color_red);
	current.blocks[1][2].pos.x += 1;
	current.blocks[1][2].pos.y -= 1;
	
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
	return (bl.pos.x >= 0) || (bl.pos.y >= 0);
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