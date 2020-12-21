#pragma once
#include "freq_table.h"
#include "huffman_tree.h"
#include "coding_table.h"

namespace huff {
	class huffman_list_node {
	public:
		huffman_list_node();
		huffman_list_node(char letter, double perc );
		~huffman_list_node();

		huffman_list_node& get_next() const { return *next; }
		huffman_tree &get_tree()  { return tree; }
		void set_next(huffman_list_node *next) { this->next = next; }
		void set_tree(huffman_tree tree) { this->tree = tree; }

	private:
		huffman_list_node* next{};
		huffman_tree tree{};
	};

	class huffman_list {
	public:
		huffman_list();
		~huffman_list();
		void create_huffman_list(freq_table &freq_table);
		void prepend_node(const char &c, const double &p);
		void print_huffman_list() const;
		void create_huffman_tree();
		coding_table create_coding_table();

	private:
		huffman_list_node* head{ nullptr };
		size_t list_size{ 0 };
	};
}