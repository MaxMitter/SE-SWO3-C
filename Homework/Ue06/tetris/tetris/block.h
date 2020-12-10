#ifndef BLOCK_H
#define BLOCK_H

#include "types.h"

extern bool b_try_move_block(block bl, int dx, int dy);
extern void b_move_block(block* bl, int dx, int dy);
extern block b_new_block_color(color color);

#endif