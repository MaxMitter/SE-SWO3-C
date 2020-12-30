#pragma once

#include <iostream>

#include "position.h"
#include "chessman.h"
#include "field.h"

class chessboard {

	public:
	chessboard (int height, int width);
	~chessboard ();

	// player actions
	bool select_chessman  (position &pos);
	bool move_chessman_to (position &pos);

	//useful functions
	bool is_within_field (position & pos) const;

	// getter
	bool is_running () const                { return m_game_running; };
	auto & get_field (position & pos) const { return m_board[idx(pos.row, pos.col)]; };
	int get_width () const                  { return m_width; };
	int get_height () const                 { return m_height; };
	chessman * get_selected () const        { return m_p_selected; };
	color get_player () const               { return m_turn; };

	private:
	int        m_height{};
	int        m_width{};
	bool	   m_game_running{};
	chessman * m_p_selected{};
	color	   m_turn{};
	field *    m_board{};

	// print stuff
	std::string get_player_string () const;
	void print () const;
	void print_legend (int len) const;
	void print_separator (int len) const;
	void print_turn () const;

	// private functions
	int idx (int row, int col) const;
	void move_to (position & pos);
	void next_turn ();
	void reset_actions ();
	void evaluate_possible_destinations ();
	bool destinations_found () const;

	// tie check
	bool check_next_player_can_move ();

};
