#pragma once

#include "position.h"

class chessboard;

typedef enum color {
	black,
	white
} color;

// virtual class
class chessman {

	public:
	// getter
	auto & get_pos () const    { return m_pos; };
	auto & get_name () const   { return m_name; };
	auto & get_color () const  { return m_color; };
	bool is_essential () const { return m_is_essential; };
	
	// setter
	void set_pos (position & pos) { m_pos = pos; };

	// interface for path checking
	virtual bool can_move_to (chessboard & cb, position & pos) const = 0;

	protected:
	explicit chessman (char name, color c, int row, int col, bool essential = false);

	// path checking methods (universally usable)
	bool check_line(chessboard & cb, position dpos, position & dest) const;
	bool move_or_capture (chessboard & cb, position & newpos) const;
	bool move (chessboard & cb, position & newpos) const;
	bool capture (chessboard & cb, position & newpos) const;
	bool move_or_capture_not_threatened(chessboard & cb, position dpos, position & dest) const;
	bool threatened (chessboard & cb, position dpos) const;

	private:
	position m_pos{};
	char	 m_name{};
	color    m_color{};
	bool     m_is_essential{};
};

