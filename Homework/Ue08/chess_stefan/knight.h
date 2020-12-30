#pragma once

#include "./chessman.h"

class knight : public chessman {

	public:
	knight (color c, int row, int col);

	protected:
	bool can_move_to (chessboard & cb, position & dest) const override;

};

