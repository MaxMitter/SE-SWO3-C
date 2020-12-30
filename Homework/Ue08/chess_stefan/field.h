#pragma once

#include "./chessman.h"

// action defines what player can do after selecting figure
typedef enum action {
	none,             // default
	selected,         // currently selected
	valid_destination // can move there
} action;

class field {

	public:
	field();
	~field();
	void print (int row, int col) const;

	// getter
	auto & get_reference () const { return m_p_figure; };
	action get_action () const { return m_action; };

	// setter
	void set_reference (chessman * figure);
	void set_action (action act) { m_action = act; };

	private:
	action	   m_action{};
	chessman * m_p_figure{};
};

