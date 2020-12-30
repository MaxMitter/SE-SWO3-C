#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <Windows.h>
//#include <vld.h>

#include "position.h"
#include "chessboard.h"

#define PVE 1
#define EVE 2

static
void get_valid_pos (const chessboard & cb, position & pos) {
	std::string input;
	int row, col;

	// read pos until it results in allowed move/selection
	do {
		if (cb.get_selected() == nullptr) {
			std::cout << "Select figure: ";
		} else {
			std::cout << "Move figure to: ";
		} // if
		std::cin >> input;

		// get first 2 characters for pos
		row = cb.get_height() - atoi(input.substr(1, input.length() - 1).c_str());
		col = input[0] - 'a';

		pos.row = row; pos.col = col;
	} while (!(cb.is_within_field(pos)));
	
}

// sets gameboard dimensions
// smallest is 5x5, largest 99x26 (not recommended)
static
chessboard * set_gameboard_dimensions () {
	// read c++ string, convert to c string
	// use atoi for int value
	std::string h_str, w_str;
	std::cout << "Enter size for your chessboard!\n";
	std::cout << "Heigth (5 - 99): "; std::cin >> h_str;
	std::cout << "Width  (8 - 26): "; std::cin >> w_str;

	// try to convert into integer
	// if invalid, smallest size will be used
	int h = atoi(h_str.c_str());
	int w = atoi(w_str.c_str());
	chessboard * p_cb = new chessboard{h, w};
	return p_cb;
}

static
void player_vs_player (chessboard & cb) {
	position pos{};

	while (cb.is_running()) {
		get_valid_pos (cb, pos);
		bool could_select = cb.select_chessman(pos);
		if (could_select) {
			bool could_move = false;
			do {
				get_valid_pos (cb, pos);
				could_move = cb.move_chessman_to(pos);
			} while (!could_move);
		} // if
	} // while
}

static
void get_random_pos (const chessboard & cb, position & pos) {
	pos.row = rand() % cb.get_height();
	pos.col = rand() % cb.get_width();
}

static
int max2 (int x, int y) {
	return (x > y) ? (x) : (y);
}

static
void computer_vs_computer (chessboard & cb) {
	position pos{};
	std::srand(std::time(nullptr));

	std::string delay_str;
	std::cout << "Select delay between moves: ";
	std::cin >> delay_str;
	int delay = max2 (atoi(delay_str.c_str()), 100) / 2;

	while (cb.is_running()) {
		get_random_pos (cb, pos);
		bool could_select = cb.select_chessman (pos);
		if (could_select) {
			Sleep(delay);
			bool could_move = false;
			do {
				get_random_pos (cb, pos);
				could_move = cb.move_chessman_to (pos);
			} while (!could_move);
			Sleep(delay);
		} // if
	} // while
}

void player_vs_computer (chessboard & cb) {
	position pos{};
	std::srand(std::time(nullptr));

	while (cb.is_running()) {
		if (cb.get_player() == white) {
			get_valid_pos (cb, pos);
		} else {
			get_random_pos (cb, pos);
		} // if
		bool could_select = cb.select_chessman(pos);
		if (could_select) {
			bool could_move = false;
			do {
				if (cb.get_player() == white) {
					get_valid_pos (cb, pos);
				} else {
					get_random_pos (cb, pos);
				} // if
				could_move = cb.move_chessman_to(pos);
			} while (!could_move);
		} // if
	} // while
}

int main() {

	chessboard * cb = set_gameboard_dimensions ();

	std::string selection_str;
	std::cout << "PvP (0) | PvE (1) | EvE (2): "; std::cin >> selection_str;

	// invalid input means PvP
	int selection = atoi(selection_str.c_str());

	switch (selection) {
		case PVE:
			player_vs_computer(*cb);
			break;
		case EVE:
			computer_vs_computer (*cb);
			break;
		default:
			player_vs_player (*cb);
	} // switch

	delete cb;

	return EXIT_SUCCESS;

} // main