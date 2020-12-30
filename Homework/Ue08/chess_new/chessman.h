#pragma once

#include "position.h"

typedef enum color {
	white,
	black
};


class chessman {

	public:
		auto& get_pos() const { return this->pos; }
		auto& get_name() const { return this->piece; }
		auto& get_color() const { return this->col; }

	private:
		position pos{};
		char piece{};
		color col{};
		bool is_essential{};
};