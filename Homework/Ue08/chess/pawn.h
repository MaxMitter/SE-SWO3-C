#pragma once
#include "chessman.h"

class pawn : public chessman {
public:
	pawn(int row, int col, color clr) :
		chessman{ row, col, (clr == white ? 'P' : 'p'), clr } {}

	bool can_move(gameboard &gb, position delta) override;
private:
};