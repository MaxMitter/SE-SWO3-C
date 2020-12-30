#include <iostream>
#include <iomanip>
#include <cmath>

#include "chessboard.h"

#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "pawn.h"
#include "chessman.h"

chessboard::chessboard (int height, int width)
	: m_height		{std::min(std::max(height, 5), 99)}
	, m_width		{std::min(std::max(width, 8), 26)}
	, m_turn		{color::white}
	, m_game_running{true}
	, m_p_selected  {nullptr}
	, m_board       {new field[m_height * m_width]} {

	// create figures based on size

	//m_board[idx(m_height - 1, m_width / 2)].set_reference(new king{color::white, newpos});
	//m_board[idx(0, (m_width / 2)) - ((m_width % 2 == 0) ? (1) : (0))].set_reference(new king{color::black, newpos});
	
	// white - hardcoded

	m_board[idx(m_height - 1, 0)].set_reference(new rook{color::white, m_height - 1, 0});
	m_board[idx(m_height - 1, 1)].set_reference(new knight{color::white, m_height - 1, 1});
	m_board[idx(m_height - 1, 2)].set_reference(new bishop{color::white, m_height - 1, 2});
	m_board[idx(m_height - 1, 3)].set_reference(new queen{color::white, m_height - 1, 3});
	m_board[idx(m_height - 1, 4)].set_reference(new king{color::white, m_height - 1, 4});
	m_board[idx(m_height - 1, 5)].set_reference(new bishop{color::white, m_height - 1, 5});
	m_board[idx(m_height - 1, 6)].set_reference(new knight{color::white, m_height - 1, 6});
	m_board[idx(m_height - 1, 7)].set_reference(new rook{color::white, m_height - 1, 7});
	
	for (int i = 0; i < m_width; i++) {
		m_board[idx(m_height - 2, i)].set_reference(new pawn{color::white, m_height - 2, i});
	} // for
	
	m_board[idx(0, m_width - 8)].set_reference(new rook{color::black, 0, m_width - 8});
	m_board[idx(0, m_width - 7)].set_reference(new knight{color::black, 0, m_width - 7});
	m_board[idx(0, m_width - 6)].set_reference(new bishop{color::black, 0, m_width - 6});
	m_board[idx(0, m_width - 5)].set_reference(new king{color::black, 0, m_width - 5});
	m_board[idx(0, m_width - 4)].set_reference(new queen{color::black, 0, m_width - 4});
	m_board[idx(0, m_width - 3)].set_reference(new bishop{color::black, 0, m_width - 3});
	m_board[idx(0, m_width - 2)].set_reference(new knight{color::black, 0, m_width - 2});
	m_board[idx(0, m_width - 1)].set_reference(new rook{color::black, 0, m_width - 1});
	
	for (int i = 0; i < m_width; i++) {
		m_board[idx(1, i)].set_reference(new pawn{color::black, 1, i});
	} // for

	for (int i = 8; i < m_width; i++) {
		m_board[idx(0, m_width - i - 1)].set_reference(new rook{color::black, 0, m_width - i - 1});
		m_board[idx(m_height - 1, i)].set_reference(new rook{color::white, m_height - 1, i});
	}

	print ();
	print_turn ();
}

chessboard::~chessboard () {
	delete [] m_board;
}

// attempts to select figure based on specified position
bool chessboard::select_chessman (position &pos) {
	
	field & curr_field  = get_field(pos);
	chessman * p_select = curr_field.get_reference();

	if (p_select != nullptr) {
		// selected figure matches player color
		if (p_select->get_color() == m_turn) {
			m_p_selected = p_select;

			curr_field.set_action (selected);
			evaluate_possible_destinations ();
			if (destinations_found ()) {
				print ();
				print_turn();
				return true;
			} else {
				reset_actions();
				m_p_selected = nullptr;
				return false;
			}
		} else {
			return false;
		} // if
	} else {
		return false;
	} // if
}

void chessboard::evaluate_possible_destinations () {
	for (int i = 0; i < get_width(); i++) {
		for (int j = 0; j < get_height(); j++) {
			position curr_pos = position{i, j};
			chessman * p_enemy = get_field(curr_pos).get_reference();
			if ((p_enemy == nullptr || p_enemy->get_color() != m_turn)
				&& m_p_selected->can_move_to(*this, curr_pos)) {
				m_board[idx(i, j)].set_action(valid_destination);
			} // if
		} // for
	} // for
}

bool chessboard::destinations_found () const {
	bool found_dest = false;
	for (int i = 0; i < get_width() && !found_dest; i++) {
		for (int j = 0; j < get_height() && !found_dest; j++) {
			position curr_pos = position{i, j};
			field & p_field = get_field(curr_pos);
			if (p_field.get_action() == valid_destination) {
				found_dest = true;
			} // if
		} // for
	} // for
	return found_dest;
}

// attempts to move selected figure to specified position
bool chessboard::move_chessman_to (position & pos) {
	// a figure has to be selected for this
	if (m_p_selected) {
		field & dest_field = get_field(pos);
		// can you move there?
		if (dest_field.get_action() == valid_destination) {
			chessman * other_figure = dest_field.get_reference();

			// if enemy chessman captured, delete it
			if (other_figure != nullptr) {
				// update game condition if necessary
				if (other_figure->is_essential()) {
					m_game_running = false;
				} // if

				delete other_figure;
			} // if
			move_to (pos);
			return true;
		} else {
			return false;
		} // if
	} else {
		return false;
	} // if
}

// checks if specified position is within chessboard
bool chessboard::is_within_field (position & pos) const {
	return pos.col < m_width && pos.row < m_height
			&& pos.col >= 0 && pos.row >= 0;
}

// logically moves selected figure to destination
// deletes enemy figure if captured
void chessboard::move_to (position & pos) {
	position curr_pos = m_p_selected->get_pos();

	get_field(pos).set_reference(m_p_selected);
	get_field(curr_pos).set_reference(nullptr);
	m_p_selected->set_pos(pos);
	m_p_selected = nullptr;
	reset_actions ();
	print ();

	// did enemy lose essential unit?
	if (m_game_running) {
		next_turn ();
		print_turn ();
		// check if next player could move
		
		if (!check_next_player_can_move ()) {
			// check if next player could move (tie detection)
			next_turn ();
			if (check_next_player_can_move ()) {
				next_turn ();
				std::cout << get_player_string() << "can no longer move!\n";
			} else {
				std::cout << "(nice) tie!\n";
			} // if
			next_turn ();
			m_game_running = false;
		} // if
		
	} else {
		std::cout << get_player_string() << " won the game!\n";
	} // if
}

void chessboard::reset_actions () {
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			m_board[idx(i, j)].set_action(none);
		} // for
	} // for
}

// updates player turn
void chessboard::next_turn () {
	(m_turn == white) ? (m_turn = black) : (m_turn = white);
}

// private functions
// calculates m_board index from two coordinates
int chessboard::idx (int row, int col) const {
	return row * m_width + col;
}

// prints chessboard
void chessboard::print () const {
	
	system("CLS");
	int len = int(trunc(log10(m_height)) + 1);

	print_legend (len);
	print_separator (len);

	for (int i = 0; i < m_height; i++) {
		std::cout << std::setw(len) << m_height - i << " |";
		for (int j = 0; j < m_width; j++) {
			m_board[idx(i, j)].print(i, j);
		} // for
		std::cout << "| " << std::setw(len) << m_height - i << "\n";
	} // for

	print_separator (len);
	print_legend (len);
	std::cout << "\n";
}

// prints top/bottom coordinate infos
void chessboard::print_legend (int len) const {
	std::cout << std::setw(len) << " " << " |";
	for (int i = 0; i < m_width; i++)
		std::cout << " " << char(i + 'a') << " ";
	std::cout << "|" << "\n";
}

// --+---...---+-- adjusted to size
void chessboard::print_separator (int len) const {
	for (int i = 0; i <= len; i++)
		std::cout << "-";
	std::cout << "+";
	for (int i = 0; i < m_width; i++)
		std::cout << "---";
	std::cout << "+";
	for (int i = 0; i <= len; i++)
		std::cout << "-";
	std::cout << "\n";
}

void chessboard::print_turn () const {
	std::cout << "Turn: "
		<< ((m_turn == black) ? ("black") : ("white")) << "\n";
}

std::string chessboard::get_player_string () const {
	return ((m_turn == black) ? ("black") : ("white"));
}

// check if next player could move
bool chessboard::check_next_player_can_move () {


	//evaluate_possible_destinations ();
	//bool can_move_once = destinations_found ();

	//reset_actions ();

	return true;
}