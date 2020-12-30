#include <iostream>
#include <iomanip>
#include "gameboard.h"
#include "pawn.h"
#include "king.h"

#define MAX_HEIGHT 99
#define MAX_WIDTH 26

gameboard::gameboard(int height, int width) {
	if (height < 5 || height > MAX_HEIGHT)
		height = 5;
	// maximum 26 for 26 Letters
	if (width < 8 || width > MAX_WIDTH)
		width = 8;

	this->height = height;
	this->width = width;
	this->board = new square[height * width];

	this->selected_figure = nullptr;
	this->current_turn = white;
}

gameboard::~gameboard() {
	delete[] this->board;
}

void gameboard::debug(std::string level) {
	std::cout << "################### Debug: " << level << std::endl;
	if (level == "board") {
		for (int i = 1; i <= this->height; i++) {
			for (int j = 1; j <= this->width; j++) {
				chessman* fig = this->board[coord_to_array(i, j)].get_figure();
				if (fig == nullptr)
					std::cout << "[" << i << "," << j << "] = null" << std::endl;
				else
					std::cout << "[" << i << "," << j << "] = " << fig->get_color()
							<< ", " << fig->get_figure() << ", " << std::endl;
			}
		}
	}
}

void draw_line(int size) {
	for (int i = 0; i < size + 1; i++) {
		if (i == 0)
			std::cout << " --+";
		else if (i == size)
			std::cout << "---+--";
		else
			std::cout << "---";
	}
}

void gameboard::draw_board() {
	system("CLS");

	std::cout << "   |";
	for (int i = 0; i < width; i++) {
		std::cout << " " << char(i + 'a') << " ";
	}
	std::cout << "|  \n";

	draw_line(this->width);

	for (int i = height; i > 0; i--) {
		if (i < 10) {
			std::cout << std::endl << " " << i << " |";
		}	
		else
			std::cout << std::endl << i << " |";

		for (int j = 1; j <= width; j++) {
			this->board[coord_to_array(i, j)].print(position{ i, j });
		}

		if (i < 10) {
			std::cout << "| " << i << " ";
		}
		else
			std::cout << "|" << i;
	}

	std::cout << std::endl;
	draw_line(this->width);

	std::cout << "\n   |";
	for (int i = 0; i < width; i++) {
		std::cout << " " << char(i + 'a') << " ";
	}
	std::cout << "|  \n";
}

int gameboard::pos_to_array(position pos) const {
	// both values - 1 for 0 based index
	return ((pos.row - 1) * this->width + pos.col - 1);
}

int gameboard::coord_to_array(int row, int col) const {
	// both values - 1 for 0 based index
	return ((row - 1) * this->width + col - 1);
}

void gameboard::move_figure(position old_pos, position new_pos) {
	/*for (int i = 0; i < MAX_PIECES_PER_COLOR * 2; i++) {
		this->figures[i]->get_position();

		if (this->figures[i]->get_position() == old_pos) {
			this->move_figure(this->figures[i], new_pos);
			break;
		}
	}*/
}

void gameboard::move_figure(chessman* figure, position new_pos) {
	/*int new_pos_in_array = -1;
	position old_pos = figure->get_position();
	if (old_pos.row == -1 && old_pos.col == -1) {
		figure->set_position(new_pos);
		new_pos_in_array = pos_to_array(new_pos);
		this->board[new_pos_in_array] = figure->get_figure();
	} else {
		position delta = new_pos + old_pos;
		if (figure->move(delta)) {
			int old_pos_in_array = pos_to_array(old_pos);
			new_pos_in_array = pos_to_array(new_pos);
			this->board[new_pos_in_array] = this->board[old_pos_in_array];
			this->board[old_pos_in_array] = '\0';
		}
	}*/
}

void gameboard::init_board() {
	
	int middle = (this->width % 2 == 0 ? int(this->width / 2) : int((this->width - 1) / 2));

	//default white pieces
	this->board[coord_to_array(this->height, middle - 3)].set_figure(new king{ this->height, middle - 3, black });
	this->board[coord_to_array(this->height, middle - 2)].set_figure(new king{ this->height, middle - 2, black });
	this->board[coord_to_array(this->height, middle - 1)].set_figure(new king{ this->height, middle - 1, black });
	this->board[coord_to_array(this->height, middle)].set_figure(new king{ this->height, middle, black });
	this->board[coord_to_array(this->height, middle + 1)].set_figure(new king{ this->height, middle + 1, black });
	this->board[coord_to_array(this->height, middle + 2)].set_figure(new king{ this->height, middle + 2, black });
	this->board[coord_to_array(this->height, middle + 3)].set_figure(new king{ this->height, middle + 3, black });
	this->board[coord_to_array(this->height, middle + 4)].set_figure(new king{ this->height, middle + 4, black });

	for (int i = 1; i <= this->width; i++) {
		this->board[coord_to_array(this->height - 1, i)].set_figure(new pawn{ this->height - 1, i , black });
	}

	this->board[coord_to_array(1, middle - 3)].set_figure(new king{ this->height, middle - 3, white });
	this->board[coord_to_array(1, middle - 2)].set_figure(new king{ this->height, middle - 2, white });
	this->board[coord_to_array(1, middle - 1)].set_figure(new king{ this->height, middle - 1, white });
	this->board[coord_to_array(1, middle)].set_figure(new king{ this->height, middle, white });
	this->board[coord_to_array(1, middle + 1)].set_figure(new king{ this->height, middle + 1, white });
	this->board[coord_to_array(1, middle + 2)].set_figure(new king{ this->height, middle + 2, white });
	this->board[coord_to_array(1, middle + 3)].set_figure(new king{ this->height, middle + 3, white });
	this->board[coord_to_array(1, middle + 4)].set_figure(new king{ this->height, middle + 4, white });

	for (int i = 1; i <= this->width; i++) {
		//this->board[coord_to_array(2, i)].set_figure(new pawn{ 2, i , white });
	}

	this->draw_board();
}

chessman* gameboard::get_figure_on_pos(position pos) {
	return this->board[pos_to_array(pos)].get_figure();
}

bool gameboard::is_valid_pos(position& pos) const {
	if (pos.row > 0 && pos.row < MAX_HEIGHT &&
		pos.col > 0 && pos.col < MAX_WIDTH) {
		return true;
	}

	return false;
}

square& gameboard::get_square(position pos) {
	return this->board[pos_to_array(pos)];
}

bool gameboard::calculate_targets() {
	bool found_target = false;
	for (int i = 1; i <= this->width; i++) {
		for (int j = 1; j <= this->height; j++) {
			position current_pos = position{ i, j };
			chessman* target_figure = get_square(current_pos).get_figure();
			if ((target_figure == nullptr || target_figure->get_color() != this->current_turn)
				&& this->selected_figure->can_move(*this, current_pos)) {
				this->board[pos_to_array(current_pos)].set_state(valid_dest);
				found_target = true;
			}
		}
	}

	return found_target;
}

bool gameboard::select_figure(position pos) {
	square& current_square = get_square(pos);
	chessman* figure = current_square.get_figure();

	if (figure != nullptr) {
		if (figure->get_color() == this->current_turn) {
			current_square.set_state(selected);
			this->selected_figure = figure;
			if (calculate_targets()) {
				this->draw_board();
				return true;
			}
		}
	}
	return false;
}