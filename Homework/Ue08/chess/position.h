#pragma once

class position {
	public:
		position(int row = 0, int col = 0) { this->row = row; this->col = col; }
		position(const position& copy) { this->row = copy.row; this->col = copy.col; }

		int row{ 0 };
		int col{ 0 };

		position& add(int dr, int dc) {
			static position temp{};
			temp.row = this->row + dr;
			temp.col = this->col + dc;
			return temp;
		}

		position& operator+= (const position& other) {
			row += other.row;
			col += other.col;
			return *this;
		}

		position& operator+ (const position& other) {
			position temp{ this->row + other.row,
						   this->col + other.col };
			return temp;
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