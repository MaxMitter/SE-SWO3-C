#include "huffman_tree.h"
#include <iostream>

namespace huff {
//huffman_tree_node///////////////////////////////////////////////////////
	huffman_tree_node::huffman_tree_node() {
	}

	huffman_tree_node::huffman_tree_node(char letter, double perc) 
		: c { letter },
		  p{ perc },
		  left { nullptr },
		  right{ nullptr } {
	}

	huffman_tree_node::~huffman_tree_node() {
	}


//huffman_tree///////////////////////////////////////////////////////////
	huffman_tree::huffman_tree() {
	}

	huffman_tree::huffman_tree(char letter, double perc)
		: head{ letter, perc } {
	}

	huffman_tree::~huffman_tree() {
	}

	void print_tree_rec(huffman_tree_node* tree) {
		if (tree != nullptr) {
			std::cout << tree->get_c() << " " << tree->get_p() << "\n";
			print_tree_rec(tree->get_left());
			print_tree_rec(tree->get_right());
		}
	}

	void huffman_tree::print_huffman_tree() {
		print_tree_rec(&head);
	}
}