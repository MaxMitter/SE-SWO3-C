#pragma once

#include "chessman.h"

class king : public chessman {
	public:
		king(int row, int col, color clr) : 
			chessman{ row, col, (clr == white ? 'K' : 'k'), clr } {}

		bool can_move(gameboard &board, position new_pos) override;
	private:
};