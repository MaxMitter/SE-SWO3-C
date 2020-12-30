#pragma once

#include "./chessman.h"

class king : public chessman {

	public:
	king (color c, int row, int col);

	protected:
	bool can_move_to (chessboard & cb, position & dest) const override;
};