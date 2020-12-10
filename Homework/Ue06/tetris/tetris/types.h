#ifndef TYPES_H
#define TYPES_H

#include <assert.h>
#include <stdbool.h>

#define GB_ROWS 22
#define GB_COLS 11
//Used to define the maximum size a piece can have on 1 axis
#define FIGURE_MAX_SIZE 4

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
	color_orange  = color_red   | color_green / 2
} color;

typedef enum { I, O, T, L, J, S, Z} shape;

typedef struct {
	int x, y;
} position;

typedef struct {
	position pos;
	color color;
} block;

typedef struct {
	block blocks[FIGURE_MAX_SIZE][FIGURE_MAX_SIZE];
	shape figure_shape;
} figure;

typedef struct {
	figure piece;
	position translation;
} rotation;

extern void render_quad(const position pos, const color color);
extern void render_block(const block block);
extern void render_figure(const figure figure);

#endif