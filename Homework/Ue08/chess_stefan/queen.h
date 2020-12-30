#pragma once

#include "./chessman.h"

class queen : public chessman {

	public:
	queen (color c, int row, int col);

	protected:
	bool can_move_to (chessboard & cb, position & dest) const override;
};

