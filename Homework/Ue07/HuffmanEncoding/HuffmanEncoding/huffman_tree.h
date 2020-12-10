#pragma once

class huffman_tree_node {
	public:
		huffman_tree_node(const char car = '-', const int p = 0);

		bool operator< (huffman_tree_node other);
		bool operator> (huffman_tree_node other);

		bool has_left_node();
		bool has_right_node();

		huffman_tree_node* get_left();
		huffman_tree_node* get_right();

		void insert_left(huffman_tree_node* node);
		void insert_right(huffman_tree_node* node);

		void print();

	private:
		char character;
		int frequency;
		huffman_tree_node* left;
		huffman_tree_node* right;
};

class huffman_tree {
	public:
		huffman_tree();

		void insert_node(huffman_tree_node* node);

		void print();
	private:
		void insert_sorted(huffman_tree_node* curr, huffman_tree_node* node);
		void print_rec(std::string prefix, huffman_tree_node* curr, bool isLeft = false);

		huffman_tree_node* tree_ptr;
};