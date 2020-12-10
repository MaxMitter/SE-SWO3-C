#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <stdbool.h>
#include "types.h"

#define MAX_BLOCKS_COUNT ((GB_ROWS)*(GB_COLS))

static block blocks[GB_ROWS][GB_COLS];

extern bool gb_is_valid_position(const position pos);

extern void gb_add_block(const block block);
extern void gb_render(void);
extern void gb_init_game_board(void);
extern int gb_get_score(void);
extern double gb_get_interval(void);
extern void gb_set_interval(double intvl);

#endif
