#include "chessman.h"
#include "gameboard.h"
#include <iostream>

chessman::chessman(int r, int c, char figure, color col, bool essential) {
	this->pos = position{ r, c };
	this->figure = figure;
	this->fig_color = col;
}

bool chessman::move(gameboard& gb, position new_pos) const {
	if (gb.is_valid_pos(new_pos)) {
		if (gb.get_square(new_pos).get_figure() == nullptr)
			return true;
	}
	return false;
}

bool chessman::capture(gameboard& gb, position new_pos) const {
	if (gb.is_valid_pos(new_pos)) {
		chessman* other = gb.get_square(pos).get_figure();
		if (other != nullptr) {
			if (other->fig_color != this->fig_color)
				return true;
		}
	}
	return false;
}

bool chessman::is_valid_position(gameboard& gb, position pos) const {
	//return gb.is_valid_pos(pos, this->fig_color);
	return false;
}