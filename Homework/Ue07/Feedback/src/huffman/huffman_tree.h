#pragma once

namespace huff {
	class huffman_tree_node {
	public:
		huffman_tree_node();
		huffman_tree_node(char letter, double perc);
		~huffman_tree_node();

		huffman_tree_node* get_left() const { return left; }
		huffman_tree_node* get_right() const { return right; }
		char get_c() const { return c; }
		double get_p() const{ return p; }

		void set_left(huffman_tree_node *left) { this->left = left; }
		void set_right(huffman_tree_node* right) { this->right = right; }
		void set_c(char c) { this->c = c; }
		void set_p(double p) { this->p = p; }

	private:
		huffman_tree_node* left{ nullptr };
		huffman_tree_node* right{ nullptr };
		char c{ 0 };
		double p{ 0.0 };
	};

	class huffman_tree {
	public:
		huffman_tree();
		huffman_tree(char letter, double perc);
		~huffman_tree();

		huffman_tree_node *get_head() { return &head; }
		void set_head(huffman_tree_node head) { this->head = head; }

		void print_huffman_tree();

	private:
		huffman_tree_node head{};
	};
}