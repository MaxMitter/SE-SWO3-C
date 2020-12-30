#pragma once
#include "chessman.h"

enum state {
	none,
	selected,
	valid_dest
};

class square {
	public:
		square();
		~square();

		void print(position pos);

		chessman* get_figure() { return this->figure;
		}
		void set_figure(chessman* piece) { this->figure = piece; }
		void set_state(state st) { this->status = st; }

	private:	
		state status;
		chessman* figure;
};