#include <GLFW/glfw3.h>
#include "types.h"

void render_quad(const position pos, const color color) {
	static_assert(sizeof(color) == 4, "detected unexpected size for colors");
	
	glColor3ubv((unsigned char *)&color);
	
	glBegin(GL_QUADS);
    glVertex2i(pos.x,     pos.y);
    glVertex2i(pos.x,     pos.y + 1);
	glVertex2i(pos.x + 1, pos.y + 1);
	glVertex2i(pos.x + 1, pos.y);
	glEnd();
}

void render_block(const block block) {
	render_quad(block.pos, block.color);
}

void render_figure(const figure figure) {
	for (int r = FIGURE_MAX_SIZE - 1; r >= 0; r--) {
		for (int c = FIGURE_MAX_SIZE - 1; c >= 0; c--) {
			render_block(figure.blocks[r][c]);
		}
	}
}