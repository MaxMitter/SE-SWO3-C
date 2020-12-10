#pragma once
#include "frequency_table.h"
#include "huffman_list.h"
#include "huffman_tree.h"

class coding_token {
	public:
		coding_token(const std::string text = "\0");

		void create_list();
		void create_tree();
	private:
		frequency_table* table;
		huffman_list* list;
		huffman_tree* tree;
};