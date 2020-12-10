#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <stdbool.h>

extern bool ge_handle_move(int dx, int dy, int turn);
extern bool ge_is_game_over(void);
extern void ge_restart(void);

#endif
