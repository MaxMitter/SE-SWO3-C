#include "chessman.h"
#include "chessboard.h"


chessman::chessman (char name, color c, int row, int col, bool essential)
	: m_name{name} 
	, m_color{c}
	, m_pos{position{row, col}}
	, m_is_essential{essential} {
}

// marks possible spost for moving along specified path
// returns if figure could move at least once
bool chessman::check_line(chessboard & cb, position dpos, position & dest) const {
	bool keep_moving = false;
	bool can_move    = false;
	position base    = m_pos;

	// keep moving as long as no colission with figure in path
	do {
		base       += dpos;
		can_move    = move_or_capture(cb, base);
		keep_moving = can_move && cb.get_field(base).get_reference() == nullptr;
	} while (keep_moving && dest != base);

	return dest == base;
}

// checks if figure (if there is one) on specified position
// could be replaced by current figure (or if pos is free)
bool chessman::move_or_capture (chessboard & cb, position & newpos) const {
	return (move (cb, newpos) || capture (cb, newpos));
}

// checks if position is empty --> sets action on field
bool chessman::move (chessboard & cb, position & newpos) const {
	if (cb.is_within_field(newpos)) {
		return (cb.get_field(newpos).get_reference() == nullptr);
	} else {
		return false;
	} // if
}

// checks if unit on pos could be captured --> sets action on field
bool chessman::capture (chessboard & cb, position & newpos) const {
	if (cb.is_within_field(newpos)) {
		field & curr_field  = cb.get_field(newpos);
		return (curr_field.get_reference() != nullptr)
			&& curr_field.get_reference()->get_color() != cb.get_player();
	} else {
		return false;
	} // if
}

bool chessman::move_or_capture_not_threatened (chessboard & cb, position dpos, position & dest) const {
	return move_or_capture(cb, dpos) && !threatened (cb, dpos);
}

bool chessman::threatened (chessboard & cb, position dpos) const {
	
	bool     fucking_died = false;
	position king_pos     = dpos + get_pos();
	chessman * p_enemy = nullptr;

	if (cb.is_within_field(king_pos)) {

		for (int i = 0; i < cb.get_width() && !fucking_died; i++) {
			for (int j = 0; j < cb.get_height() && !fucking_died; j++) {
				position curr_pos = position{i, j};
				p_enemy = cb.get_field(curr_pos).get_reference();
				if (p_enemy != nullptr && p_enemy->get_color() != cb.get_player()) {
					fucking_died = p_enemy->can_move_to(cb, king_pos);
				} // if
			} // for
		} // for

		if (fucking_died) {
			std::cout << "died at  " << cb.get_height() - king_pos.row << "|"
				<< king_pos.col + 1 << " by "<< p_enemy->get_name() <<"\n";
		} // if
	} // if

	return fucking_died;
}