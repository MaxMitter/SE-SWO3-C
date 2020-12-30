#pragma once
#include "chessman.h"
#include "position.h"
#include "square.h"
#include "king.h"
#include <vld.h>
#include <string>

class gameboard {
	public:
		gameboard(int height = 5, int width = 8);
		~gameboard();

		void draw_board();
		void init_board();
		bool select_figure(position pos);


		void move_figure(chessman* figure, position new_pos);
		void move_figure(position old_pos, position new_pos);
		
		chessman* get_figure_on_pos(position pos);

		bool is_valid_pos(position& pos) const;
		square& get_square(position pos);

		void debug(std::string level);

	private:
		int pos_to_array(position pos) const;
		int coord_to_array(int row, int col) const;

		bool calculate_targets();

		int height{ 0 };
		int width{ 0 };
		square* board;
		chessman* selected_figure;
		color current_turn;
};