#include "gameboard.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

	cout << "Select height (5 - 99): ";
	int height = 0;
	cin >> height;
	cout << "Select width (8 - 26): ";
	int width = 0;
	cin >> width;

	gameboard a(height, width);

	a.draw_board();

	string input;

	while (true) {
		bool draw = true;
		cout << "Test input > ";
		getline(cin, input);

		if (input == "init")
			a.init_board();
		else if (input == "move") {
			cout << "Field to move to > ";
			string field;
			getline(cin, field);
			position new_pos;
			new_pos.row = stoi(field.substr(0, 1));
			new_pos.col = stoi(field.substr(1, 1));

			position oldpos{ 0, 5 };

			a.move_figure(oldpos, new_pos);
		}
		else if (input == "select") {
			cout << "Field to select > ";
			string field;
			getline(cin, field);
			position new_pos;
			new_pos.row = stoi(field.substr(0, 1));
			new_pos.col = stoi(field.substr(1, 1));

			a.select_figure(new_pos);
		}
		else if (input == "debug") {
			draw = false;
			cout << "Level: ";
			string field;
			getline(cin, field);
			a.debug(field);
		}
		else if (input == "exit")
			break;

		if (draw)
			a.draw_board();
	}
	
	return 0;
}