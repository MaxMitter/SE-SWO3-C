#include "coding_token.h"

coding_token::coding_token(const std::string text) {
	
	this->table = new frequency_table(100);
	
	for (int i = 0; i < text.length(); i++) {
		table->add_character(text[i]);
	}

	table->update_table();
}

void coding_token::create_list() {
	this->list = new huffman_list(*(this->table));
}

void coding_token::create_tree() {

}