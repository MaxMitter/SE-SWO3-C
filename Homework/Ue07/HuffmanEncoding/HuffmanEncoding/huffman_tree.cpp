#include <iostream>
#include "huffman_tree.h"

huffman_tree_node::huffman_tree_node(const char car, const int p) {
	this->character = car;
	this->frequency = p;
	this->left = nullptr;
	this->right = nullptr;
}

bool huffman_tree_node::operator< (huffman_tree_node other) {
	return this->frequency < other.frequency;
}

bool huffman_tree_node::operator> (huffman_tree_node other) {
	return this->frequency > other.frequency;
}

bool huffman_tree_node::has_left_node() {
	return this->left != nullptr;
}

bool huffman_tree_node::has_right_node() {
	return this->right != nullptr;
}

huffman_tree_node* huffman_tree_node::get_left() {
	return this->left;
}

huffman_tree_node* huffman_tree_node::get_right() {
	return this->right;
}

void huffman_tree_node::insert_left(huffman_tree_node* node) {
	this->left = node;
}

void huffman_tree_node::insert_right(huffman_tree_node* node) {
	this->right = node;
}

void huffman_tree_node::print() {
	std::cout << "C: " << this->character << " P: " << this->frequency << std::endl;
}


// ### Huffman Tree ### //

huffman_tree::huffman_tree() {
	this->tree_ptr = nullptr;
}

void huffman_tree::insert_node(huffman_tree_node* node) {
	if (this->tree_ptr == nullptr)
		this->tree_ptr = node;
	else {
		this->insert_sorted(this->tree_ptr, node);
	}
}

void huffman_tree::insert_sorted(huffman_tree_node* curr, huffman_tree_node* node) {
	if (*curr < *node) {
		if (curr->has_right_node())
			this->insert_sorted(curr->get_right(), node);
		else
			curr->insert_right(node);
	} else {
		if (curr->has_left_node())
			this->insert_sorted(curr->get_left(), node);
		else
			curr->insert_left(node);
	}
}

void huffman_tree::print() {
	this->print_rec("", this->tree_ptr);
}

void huffman_tree::print_rec(std::string prefix, huffman_tree_node* curr, bool isLeft) {
	if (curr != nullptr) {
		std::cout << prefix;

		std::string test = (isLeft ? "|--" : "|__");
		std::cout << test;

		curr->print();

		std::string new_prefix = prefix + (isLeft ? "|  " : "   ");

		print_rec(new_prefix, curr->get_left(), true);
		print_rec(new_prefix, curr->get_right(), false);
	}
}