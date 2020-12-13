#pragma once

class huffman_tree_node {
	public:
		huffman_tree_node(const char car = '-', const double p = 0);
		~huffman_tree_node();

		bool operator< (huffman_tree_node* other);
		bool operator> (huffman_tree_node* other);

		bool has_left_node();
		bool has_right_node();

		huffman_tree_node* get_left();
		huffman_tree_node* get_right();
		double get_frequency();
		char get_character();
		int count_leaves_rec();
		double calculate_freq_sum();

		void insert_left(huffman_tree_node* node);
		void insert_right(huffman_tree_node* node);

		void print();
		huffman_tree_node* operator+ (huffman_tree_node* other);

	private:
		char character;
		double frequency;
		huffman_tree_node* left;
		huffman_tree_node* right;
};

class huffman_tree {
	public:
		huffman_tree();
		huffman_tree(huffman_tree_node* first_node);
		~huffman_tree();

		void insert_node(huffman_tree_node* node);
		huffman_tree_node* get_first_node();
		void set_first_node(huffman_tree_node* node);
		int count_leaves();
		double calculate_freq_sum();
		void print();
		
	private:
		void insert_sorted(huffman_tree_node* curr, huffman_tree_node* node);
		void print_rec(std::string prefix, huffman_tree_node* curr, bool isLeft = false);

		huffman_tree_node* tree_ptr;
};