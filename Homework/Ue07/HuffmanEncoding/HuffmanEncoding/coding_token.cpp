#include "coding_token.h"
#include <iostream>

coding_token::coding_token(const string text) {
	
	this->original_text = text;
	this->encoded_text = "";
	this->decoded_text = "";
	
	this->freq_table = nullptr;
	this->list = nullptr;
	this->tree = nullptr;
	this->code_table = nullptr;
}

coding_token::~coding_token() {
	if (this->code_table != nullptr) {
		delete this->code_table;
		this->code_table = nullptr;
	}
	if (this->tree != nullptr) {
		delete this->tree;
		this->tree = nullptr;

		auto list_entry = this->list->get_first_entry();
		//only true, if the entire tree was created successfully
		if (!list_entry->has_next() && list_entry->get_character() == '\0')
			list_entry->set_tree(nullptr);
		//has to be set to nullptr, otherwise list-deconstructor tries
		//to deconstruct already freed tree
	}
	if (this->list != nullptr) {
		delete this->list;
		this->list = nullptr;
	}
		
	if (this->freq_table != nullptr) {
		delete this->freq_table;
		this->freq_table = nullptr;
	}
}

void coding_token::delete_trees_in_list() {
	auto curr = this->list->get_first_entry();
	while (curr != nullptr) {
		if (curr->has_tree())
			delete curr->get_tree();

		curr = curr->get_next();
	}
}

void coding_token::create_freq_table() {
	if (this->original_text == "") {
		std::cout << "Text is empty, please create a new token with Text.";
		exit(-1);
	}
	int len = this->count_unique_chars();
	this->freq_table = new frequency_table(len);
	
	for (int i = 0; i < this->original_text.length(); i++) {
		this->freq_table->add_character(this->original_text[i]);
	}

	this->freq_table->update_table();
}

void coding_token::create_list() {
	if (this->freq_table == nullptr)
		this->create_freq_table();
	
	this->list = new huffman_list(this->freq_table);
}

void coding_token::create_tree() {
	if (this->list == nullptr)
		this->create_list();

	create_tree_rec(this->list);
}

void coding_token::create_coding_table() {
	if (this->tree == nullptr)
		this->create_tree();

	this->code_table = new coding_table(this->tree->count_leaves());
	this->fill_code_table(this->tree->get_first_node(), "");
}

void coding_token::fill_code_table(huffman_tree_node* cur_node, string code) {
	if (cur_node->has_left_node() && cur_node->has_right_node()) {
		fill_code_table(cur_node->get_right(), code + "1");
		fill_code_table(cur_node->get_left(), code + "0");
	} else {
		this->code_table->add_entry(cur_node->get_character(), code);
	}
}

void coding_token::print_freq_table() {
	if (this->freq_table != nullptr) {
		std::cout << "Printing Frequency Table: " << std::endl;

		this->sort_freq_table();
		this->freq_table->print();
		std::cout << "------------------------------------------" << std::endl;
	}
}

void coding_token::sort_freq_table() {
	if (this->freq_table == nullptr) {
		std::cout << "Frequency Table empty, please fill first." << std::endl;
	} else {
		int len = this->freq_table->get_length();
		auto table = this->freq_table->get_table();
		for (int i = 0; i < len - 1; i++) {
			for (int j = i + 1; j < len; j++) {
				if (table[j].get_frequency() > table[i].get_frequency()) {
					auto temp = table[i];
					table[i] = table[j];
					table[j] = temp;
				}
			}
		}
	}
}

void coding_token::print_list() {
	//Recreate List for printing if tree exists:
	if (this->tree != nullptr) {
		auto entry = this->list->get_first_entry();
		entry->set_tree(nullptr);
		delete this->list;
		this->create_list();
	}

	if (this->list != nullptr) {
		std::cout << "Printing Huffman List: " << std::endl;

		this->list->print();
		std::cout << "------------------------------------------" << std::endl;
	}
}

void coding_token::print_tree() {
	if (this->tree != nullptr) {
		std::cout << "Printing Huffman Tree: " << std::endl;

		this->tree->print();
		std::cout << "------------------------------------------" << std::endl;
	}
}

void coding_token::print_coding_table() {
	if (this->code_table != nullptr) {
		std::cout << "Printing Coding Table: " << std::endl;

		this->code_table->print();
		std::cout << "------------------------------------------" << std::endl;
	}
}

void coding_token::print_texts() {
	if (!this->original_text.empty()) {
		std::cout << "Printing Original Text" << std::endl;
		std::cout << this->original_text << std::endl;
		std::cout << "------------------------------------------" << std::endl;
	}

	if (!this->encoded_text.empty()) {
		std::cout << "Printing Encoded Text" << std::endl;
		std::cout << this->encoded_text << std::endl;
		std::cout << "------------------------------------------" << std::endl;
	}

	if (!this->decoded_text.empty()) {
		std::cout << "Printing Decoded Text" << std::endl;
		std::cout << this->decoded_text << std::endl;
		std::cout << "------------------------------------------" << std::endl;
	}
}

void coding_token::print_size_difference() {
	if (this->original_text.empty())
		std::cout << "Original Text is empty, cannot print difference." << std::endl;
	if (this->encoded_text.empty())
		std::cout << "Encoded Text is empty, cannot print difference." << std::endl;
	else {
		int size_original = this->original_text.length() * sizeof(char) * 8;
		int size_encoded = this->encoded_text.length();
		double diff = (1 - (double)size_encoded / (double)size_original);

		std::cout.precision(4);
		std::cout << "Original Size: " << size_original << " bits" << std::endl;
		std::cout << "Encoded Size: " << size_encoded << " bits" << std::endl;

		std::cout << "Compression rate: " << diff * 100 << " %" << std::endl;
		std::cout << "------------------------------------------" << std::endl;
	}
}

void coding_token::create_tree_rec(huffman_list* list) {
	huffman_list_entry* first = list->get_first_entry();
	huffman_list_entry* second = list->get_second_entry();

	if (first == nullptr) {
		std::cout << "Error while creating Tree in Recursive function: No node in list";
		exit(-1);
	} else {
		if (second == nullptr) {
			if (first->has_tree()) {
				this->tree = first->get_tree();
				return;
			} else {
				std::cout << "Error while creating Tree in Recursive function: No Tree found.";
				exit(-1);
			}
		} else {
			if (first->has_tree() && second->has_tree()) {
				auto new_tree = merge_trees(first->get_tree(), second->get_tree());
				list->remove_second_entry();
				list->remove_first_entry();
				list->add_entry(new_tree);
			} else if (first->has_tree()) {
				auto new_node = new huffman_tree_node(second->get_character(), second->get_frequency());
				auto new_tree = merge_trees(first->get_tree(), new huffman_tree(new_node));
				list->remove_second_entry();
				list->remove_first_entry();
				list->add_entry(new_tree);
			}
			else if (second->has_tree()) {
				auto new_node = new huffman_tree_node(first->get_character(), first->get_frequency());
				auto new_tree = merge_trees(new huffman_tree(new_node), second->get_tree());
				list->remove_second_entry();
				list->remove_first_entry();
				list->add_entry(new_tree);
			} else {
				auto new_node_left = new huffman_tree_node(first->get_character(), first->get_frequency());
				auto new_node_right = new huffman_tree_node(second->get_character(), second->get_frequency());
				auto new_tree = merge_trees(new huffman_tree(new_node_left), new huffman_tree(new_node_right));
				list->remove_second_entry();
				list->remove_first_entry();
				list->add_entry(new_tree);
			}
		}
		this->create_tree_rec(list);
	}
}

huffman_tree* coding_token::merge_trees(huffman_tree* left, huffman_tree* right) {
	auto left_node = left->get_first_node();
	auto right_node = right->get_first_node();
	left->set_first_node(nullptr);
	right->set_first_node(nullptr);
	delete left;
	delete right;
	auto new_node = *left_node + right_node;
	return new huffman_tree(new_node);
}

int coding_token::count_unique_chars() {
	if (original_text != "") {
		string chars = "";
		for (int i = 0; i < original_text.length(); i++) {
			if (chars.find(original_text[i]) == string::npos) {
				chars += original_text[i];
			}
		}
		return chars.length();
	}
	return 0;
}

string coding_token::encode() {
	if (this->code_table == nullptr)
		this->create_coding_table();

	for (int i = 0; i < this->original_text.length(); i++) {
		this->encoded_text += this->code_table->get_code(this->original_text[i]);
	}

	return this->encoded_text;
}

string coding_token::decode() {
	if (this->encoded_text == "") {
		std::cout << "Text not encoded yet, please encode before trying to decode!" << std::endl;
	} else {
		string code = "";
		for (int i = 0; i < this->encoded_text.length(); i++) {
			code += this->encoded_text[i];
			if (this->code_table->is_valid_code(code)) {
				this->decoded_text += this->code_table->get_character(code);
				code = "";
			}
		}

		int compare = this->original_text.compare(this->decoded_text);
		if (compare == 0) {
			std::cout << "Encoding and decoding successfull, strings are the same!" << std::endl;
		}

		return this->decoded_text;
	}

	return "";
}

bool coding_token::text_empty() {
	return this->original_text.empty();
}