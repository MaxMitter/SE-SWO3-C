#ifndef FIGURES_H
#define FIGURES_H

#include "types.h"
#include "block.h"
#include <stddef.h>
#include <assert.h>

extern bool fg_try_move(int dx, int dy);
extern figure fg_new_figure(void);
extern figure fg_get_current(void);
extern void fg_render(void);
extern bool is_block(block bl);
extern bool fg_try_rotate_figure(void);

#endif // !FIGURES_H