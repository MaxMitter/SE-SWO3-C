#ifndef TYPES_H
#define TYPES_H

#include <assert.h>
#include <stdbool.h>

#define GB_ROWS 22
#define GB_COLS 11

#define UNUSED(var) ((void)var)

typedef enum {
	color_black   = 0x000000U,
	color_red     = 0x0000FFU,
	color_green   = 0x00FF00U,
	color_blue    = 0xFF0000U,
	color_yellow  = color_red   | color_green,
	color_magenta = color_red   | color_blue,
	color_cyan    = color_green | color_blue,
	color_white   = color_red   | color_green | color_blue,
} color;

typedef struct {
	int x, y;
} position;

extern void render_quad(const position pos, const color color);

#endif
