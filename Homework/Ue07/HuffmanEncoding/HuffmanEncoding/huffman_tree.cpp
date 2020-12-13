#include <iostream>
#include "huffman_tree.h"

huffman_tree_node::huffman_tree_node(const char car, const double p) {
	this->character = car;
	this->frequency = p;
	this->left = nullptr;
	this->right = nullptr;
}

huffman_tree_node::~huffman_tree_node() {
	if (this->left != nullptr)
		delete this->left;

	if (this->right != nullptr)
		delete this->right;
}

bool huffman_tree_node::operator< (huffman_tree_node* other) {
	return this->frequency < other->frequency;
}

bool huffman_tree_node::operator> (huffman_tree_node* other) {
	return this->frequency > other->frequency;
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

double huffman_tree_node::get_frequency() {
	return this->frequency;
}

char huffman_tree_node::get_character() {
	return this->character;
}

int huffman_tree_node::count_leaves_rec() {
	if (this->right == nullptr && this->left == nullptr) {
		return 1;
	} else {
		return this->left->count_leaves_rec() + this->right->count_leaves_rec();
	}
}

double huffman_tree_node::calculate_freq_sum() {
	if (this->left != nullptr && this->right != nullptr) {
		return this->left->calculate_freq_sum() + this->right->calculate_freq_sum();
	} else {
		return this->frequency;
	}
}

void huffman_tree_node::insert_left(huffman_tree_node* node) {
	this->left = node;
}

void huffman_tree_node::insert_right(huffman_tree_node* node) {
	this->right = node;
}

void huffman_tree_node::print() {
	if (this->character == '\0')
		std::cout << "C: " << "\\" << "0" << " P: " << this->frequency << std::endl;
	else
		std::cout << "C: " << this->character << " P: " << this->frequency << std::endl;
}

huffman_tree_node* huffman_tree_node::operator+ (huffman_tree_node* other) {
	double freq = this->frequency + other->frequency;
	auto new_node = new huffman_tree_node('\0', freq);
	new_node->left = this;
	new_node->right = other;
	return new_node;
}


// ### Huffman Tree ### //

huffman_tree::huffman_tree() {
	this->tree_ptr = nullptr;
}

huffman_tree::huffman_tree(huffman_tree_node* first_node) {
	this->tree_ptr = first_node;
}

huffman_tree::~huffman_tree() {
	delete this->tree_ptr;
}

void huffman_tree::insert_node(huffman_tree_node* node) {
	if (this->tree_ptr == nullptr)
		this->tree_ptr = node;
	else {
		this->insert_sorted(this->tree_ptr, node);
	}
}

void huffman_tree::insert_sorted(huffman_tree_node* curr, huffman_tree_node* node) {
	if (*curr < node) {
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

double huffman_tree::calculate_freq_sum() {
	return this->tree_ptr->calculate_freq_sum();
}

huffman_tree_node* huffman_tree::get_first_node() {
	return this->tree_ptr;
}

void huffman_tree::set_first_node(huffman_tree_node* node) {
	this->tree_ptr = node;
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

int huffman_tree::count_leaves() {
	return this->tree_ptr->count_leaves_rec();
}