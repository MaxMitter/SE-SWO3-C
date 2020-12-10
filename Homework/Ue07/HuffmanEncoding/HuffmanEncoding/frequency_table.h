#pragma once
#include <string>

class frequency_table_entry {
	public:
		frequency_table_entry(const char car = '\0', const int p = 0, const int c = 0);

		void update_frequency(const double total);
		void add_to_char(const int c = 1);
		void new_char(const char car, const int c);
		bool is_character(const char car);
		void print();
		char get_character();
		int get_frequency();
	private:
		char character;
		int frequency;
		int count;
};

class frequency_table {
	public:
		frequency_table(const int len = 26);

		void add_character(const char car);
		void update_table();
		void print();
		int get_length();
		frequency_table_entry* get_table();
	private:
		frequency_table_entry* table;
		int length;
		int total;
};