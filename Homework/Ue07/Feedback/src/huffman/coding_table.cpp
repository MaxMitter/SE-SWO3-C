#include "coding_table.h" 
#include <iostream>

namespace huff {
//Coding_table_entry///////////////////////////////////////////////////////////////////////
	coding_table_entry::coding_table_entry() {
	}
	coding_table_entry::~coding_table_entry() {
	}


//Coding_table///////////////////////////////////////////////////////////////////////
	coding_table::coding_table() {
	}

	coding_table::~coding_table() {
	}

	void coding_table::insert_entry(char c, std::string code) {
		entries[size].set_c(c);
		entries[size].set_code(code);
		size++;
	}

	void coding_table::print_coding_table() {
		for (size_t i = 0; i < size; i++) {
			std::cout << entries[i].get_c() << " " << entries[i].get_code() << "\n";
		}
	}

}