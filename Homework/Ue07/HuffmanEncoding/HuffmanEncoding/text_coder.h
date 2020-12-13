#pragma once
#include "coding_token.h"

enum DataType
{
	frequency_table,
	huffman_list,
	huffman_tree,
	coding_table,
	texts,
	size_difference
};

class text_coder {
	public:
		text_coder();
		text_coder(string text);
		~text_coder();

		void set_text(string text);
		bool encode();
		bool decode();

		void print_type(DataType type);

	private:
		coding_token* token;
};