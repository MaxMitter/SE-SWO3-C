#pragma once

class position {
	public:
		position(int row = 0, int col = 0) { this->row = row; this->col = col; }
		position(const position& copy) { this->row = copy.row; this->col = copy.col; }

		int row{ 0 };
		int col{ 0 };

		position& operator+= (const position& other) {
			row += other.row;
			col += other.col;
			return *this;
		}

		position& operator=(position other) {
			position temp{ other.row, other.col };
			other.row = this->row;
			other.col = this->col;
			this->row = temp.row;
			this->col = temp.col;
			return *this;
		}

		bool operator==(position& other) {
			return this->row == other.row && this->col == other.col;
		}

		bool operator!=(position& other) {
			return this->row != other.row && this->col != other.col;
		}
};