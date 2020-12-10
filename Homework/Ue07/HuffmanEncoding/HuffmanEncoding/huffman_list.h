#pragma once
#include "frequency_table.h"

class huffman_list_entry {
	public:
		huffman_list_entry(const char car, const int p);

		void set_next(huffman_list_entry* entry);
		bool has_next();
		huffman_list_entry* get_next();
		void print();
		bool frequency_is_bigger_than(const huffman_list_entry other);
		bool operator< (huffman_list_entry other);
		bool operator> (huffman_list_entry other);
	private:
		char character;
		int frequency;
		huffman_list_entry* next;
};


class huffman_list {
	public:
		huffman_list();
		huffman_list(const frequency_table table);

		void add_entry(huffman_list_entry* entry);
		void print();
	private:
		huffman_list_entry* list;
};