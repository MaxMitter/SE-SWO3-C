#pragma once

#include "./chessman.h"

class bishop : public chessman {

	public:
	bishop (color c, int row, int col);

	protected:
	bool can_move_to (chessboard & cb, position & pos) const override;

};

