#pragma once
#include "tables.h"
#include "huffman_list.h"
#include "huffman_tree.h"

using std::string;

class coding_token {
	public:
		coding_token(const string text = "\0");
		~coding_token();

		void create_freq_table();
		void create_list();
		void create_tree();
		void create_coding_table();

		void print_freq_table();
		void print_list();
		void print_tree();
		void print_coding_table();
		void print_texts();
		void print_size_difference();

		bool text_empty();

		string encode();
		string decode();
	private:

		void create_tree_rec(huffman_list* list);
		huffman_tree* merge_trees(huffman_tree* left, huffman_tree* right);
		void fill_code_table(huffman_tree_node* cur_node, string code);
		void sort_freq_table();
		void delete_trees_in_list();

		int count_unique_chars();

		string original_text;
		string encoded_text;
		string decoded_text;
		frequency_table* freq_table;
		coding_table* code_table;
		huffman_list* list;
		huffman_tree* tree;
};