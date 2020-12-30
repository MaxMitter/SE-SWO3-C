#pragma once

typedef enum square_state {
	none,
	selected,
	movable
};

class square {


	private:
		square_state state{ none };
};