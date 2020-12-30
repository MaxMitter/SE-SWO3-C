#pragma once

#include "./chessman.h"

class pawn : public chessman {

	public:
	pawn (color c, int row, int col);

	protected:
	bool can_move_to (chessboard & cb, position & dest) const override;

	private:
	bool double_move_possible (chessboard & cb) const;
};

