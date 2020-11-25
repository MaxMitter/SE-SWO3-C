#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <stdbool.h>
#include "types.h"

#define MAX_BLOCKS_COUNT ((GB_ROWS)*(GB_COLS))

static size_t block_count = 0;
static block blocks[MAX_BLOCKS_COUNT];

extern bool gb_is_valid_position(const position pos);

extern void gb_add_block(const block block);
extern void gb_render(void);

#endif
