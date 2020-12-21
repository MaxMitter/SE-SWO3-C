#pragma once
#include "freq_table.h"

namespace huff {
	class coding_table_entry {
	public:
		coding_table_entry();
		~coding_table_entry();

		char get_c() { return c; }
		std::string get_code() { return code; }
		void set_c(char c) { this->c = c; }
		void set_code(std::string code) { this->code = code; }

	private:
		char c{'\0'};
		std::string code{ '\0' };
	};

	class coding_table {
	public:
		coding_table();
		~coding_table();

		size_t get_size() { return size; };
		void set_size(size_t size) { this->size = size; };

		coding_table_entry get_entry(size_t i) { return entries[i]; }

		void print_coding_table();
		void insert_entry(char c, std::string code);

	private:
		coding_table_entry entries[MAX_SIZE];
		size_t size{ 0 };
	};
}