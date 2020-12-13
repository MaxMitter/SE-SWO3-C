#pragma once
#include <string>
#include <vld.h>

class frequency_table_entry {
	public:
		frequency_table_entry(const char car = '\0', const double p = 0.0, const int c = 0);
		
		void update_frequency(const double total);
		void add_to_char(const int c = 1);
		void new_char(const char car, const int c);
		bool is_character(const char car);

		void print();

		char get_character();
		double get_frequency();
	private:
		char character;
		double frequency;
		int count;
};

class frequency_table {
	public:
		frequency_table(const int len = 26);
		~frequency_table();

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

class coding_table_entry {
	public:	
		coding_table_entry();
		coding_table_entry(char car, std::string code);

		std::string get_code();
		void set_char(char car);
		void set_code(std::string code);
		char get_character();

		void print();
	private:
		char character;
		std::string code;
};

class coding_table {
	public:
		coding_table(int size = 100);
		~coding_table();

		void add_entry(char car, std::string code);
		std::string get_code(char car);
		char get_character(std::string code);
		bool is_valid_code(std::string code);

		void print();
	private:
		coding_table_entry* table;
		int size;
};