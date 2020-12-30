#pragma once

// used just like a struct, just offers a few funtctions for convenience
class position {
	public:
	position (int row = 0, int col = 0);
	position (const position & cpy);

	position & move_by (int drow, int dcol);

	int row{};
	int col{};

	// allows easier handling of positions

	position& operator += (const position & rhs) {
		row += rhs.row; col += rhs.col;
		return *this;
	}

	position operator + (const position & rhs) {
		position temp{*this}; return temp += rhs;
	}

	position & operator = (position rhs) {
		if (&rhs != this) {
			swap(rhs);
		} // if
		return *this;
	}

	bool operator == (position & rhs) {
		return row == rhs.row && col == rhs.col;
	}

	bool operator != (position & rhs) {
		return !(*this == rhs);
	}

	private:
	void swap (position & other);
};
