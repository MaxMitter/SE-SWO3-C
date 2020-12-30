#pragma once
#include "position.h"

class gameboard;

enum color {
	white,
	black
};

class chessman {
	public:
		//getter
		char get_figure() { return this->figure; }
		position get_position() { return this->pos; }
		color get_color() { return this->fig_color; }

		//setter
		void set_position(position pos) { this->pos = pos; }

		virtual bool can_move(gameboard &board, position delta) = 0;

		bool capture(gameboard& gb, position new_pos) const;

	protected:
		explicit chessman(int r, int c, char figure, color col, bool essential = false);

		bool is_valid_position(gameboard& gb, position pos) const;
		bool move(gameboard& gb, position new_pos) const;

	private:
		color fig_color;
		char figure;
		position pos;
		bool is_essential;
};