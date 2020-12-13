#pragma once
#include "tables.h"
#include "huffman_tree.h"

class huffman_list_entry {
	public:
		huffman_list_entry(const char car, const double p);
		huffman_list_entry(huffman_tree* tree);
		~huffman_list_entry();

		void set_next(huffman_list_entry* entry);
		void set_tree(huffman_tree* tree);
		bool has_next();
		bool has_tree();
		huffman_list_entry* get_next();
		huffman_tree* get_tree();
		void print();
		bool operator< (huffman_list_entry* other);
		bool operator> (huffman_list_entry* other);

		char get_character();
		double get_frequency();

		void free_entry(bool delete_tree);
	private:
		char character;
		double frequency;
		huffman_list_entry* next;
		huffman_tree* tree;
};


class huffman_list {
	public:
		huffman_list();
		huffman_list(frequency_table* table);
		~huffman_list();

		void add_entry(huffman_list_entry* entry);
		void add_entry(huffman_tree* tree);
		void print();
		huffman_list_entry* get_first_entry();
		huffman_list_entry* get_second_entry();

		void remove_first_entry();
		void remove_second_entry();
	private:
		huffman_list_entry* list;
};