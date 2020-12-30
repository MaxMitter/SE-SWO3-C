#pragma once

#include "./chessman.h"

class rook : public chessman {

	public:
	rook (color c, int row, int col);

	protected:
	bool can_move_to (chessboard & cb, position & dest) const override;

};

