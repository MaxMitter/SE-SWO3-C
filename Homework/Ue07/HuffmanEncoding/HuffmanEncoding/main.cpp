#include <iostream>
#include <fstream>
#include <string>
#include <new>
#include "text_coder.h"

using namespace std;

int main(int argc, char const* argv[]) {
	string line;
	string text = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	if (argc > 0) {
		/*ifstream file(argv[1]);
		if (file.is_open()) {
			while (getline(file, line)) {
				text += line;
			}
		}*/
		text_coder coder;

		coder.set_text(text);

		coder.encode();
		coder.print_type(frequency_table);
		coder.print_type(huffman_list);
		coder.print_type(huffman_tree);
		coder.print_type(coding_table);
		coder.print_type(size_difference);
		coder.decode();
		coder.print_type(texts);
	}

	return 0;
}