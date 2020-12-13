#include <iostream>
#include "huffman_list.h"

huffman_list_entry::huffman_list_entry(const char car, const double p) {
	this->character = car;
	this->frequency = p;
	this->next = nullptr;
	this->tree = nullptr;
}

huffman_list_entry::huffman_list_entry(huffman_tree* tree) {
	this->character = '\0';
	this->frequency = tree->get_first_node()->get_frequency();
	this->next = nullptr;
	this->tree = tree;
}

huffman_list_entry::~huffman_list_entry() {
	if (this->has_tree()) {
		delete this->tree;
	}
	if (this->has_next()) {
		delete this->next;
	}
}

void huffman_list_entry::set_next(huffman_list_entry* entry) {
	this->next = entry;
}

void huffman_list_entry::set_tree(huffman_tree* tree) {
	this->tree = tree;
}

bool huffman_list_entry::has_tree() {
	return this->tree != nullptr;
}

bool huffman_list_entry::has_next() {
	return this->next != nullptr;
}

huffman_list_entry* huffman_list_entry::get_next() {
	return this->next;
}

huffman_tree* huffman_list_entry::get_tree() {
	return this->tree;
}

bool huffman_list_entry::operator< (huffman_list_entry* other) {
	return this->frequency < other->frequency;
}

bool huffman_list_entry::operator> (huffman_list_entry* other) {
	return this->frequency > other->frequency;
}

void huffman_list_entry::print() {
	std::cout << "C: " << this->character << ", P: " << this->frequency << std::endl;
	if (this->has_tree()) {
		this->tree->print();
	}
}

char huffman_list_entry::get_character() {
	return this->character;
}

double huffman_list_entry::get_frequency() {
	return this->frequency;
}

void huffman_list_entry::free_entry(bool delete_tree) {
	if (delete_tree)
		delete this;
	else {
		this->tree = nullptr;
		delete this;
	}
}


// ### Huffman List ### //

huffman_list::huffman_list() {
	this->list = nullptr;
}

huffman_list::~huffman_list() {
	if (this->list->has_tree())
		delete this->list->get_tree();
	
	delete this->list;
}

huffman_list::huffman_list(frequency_table* freq_table) {
	frequency_table_entry* table = freq_table->get_table();
	this->list = nullptr;
	for (int i = 0; i < freq_table->get_length(); i++) {
		if (!table[i].is_character('\0')) {
			auto entry = new huffman_list_entry(table[i].get_character(), table[i].get_frequency());
			this->add_entry(entry);
		}
	}
}

void huffman_list::add_entry(huffman_list_entry* entry) {
	if (this->list == nullptr) {
		this->list = entry;
	} else {
		huffman_list_entry* curr = this->list;
		huffman_list_entry* prev = nullptr;
		while (curr->has_next()) {
			if (*curr < entry) {
				prev = curr;
				curr = curr->get_next();
			}
			else
				break;
		}

		if (!curr->has_next()) {
			if (*curr < entry)
				curr->set_next(entry);
			else {
				if (prev == nullptr) {
					this->list = entry;
					entry->set_next(curr);
				} else {
					prev->set_next(entry);
					entry->set_next(curr);
				}
			}
		}
		else {
			if (prev == nullptr) {
				this->list = entry;
				entry->set_next(curr);
			}
			else {
				prev->set_next(entry);
				entry->set_next(curr);
			}
		}
	}
}

void huffman_list::add_entry(huffman_tree* tree) {
	auto new_entry = new huffman_list_entry(tree);
	this->add_entry(new_entry);
}

huffman_list_entry* huffman_list::get_first_entry() {
	return this->list;
}

huffman_list_entry* huffman_list::get_second_entry() {
	if (this->list != nullptr) {
		return this->list->get_next();
	} else {
		return nullptr;
	}
}

void huffman_list::remove_first_entry() {
	if (this->list != nullptr) {
		auto temp = this->list;
		this->list = this->list->get_next();
		temp->set_next(nullptr);
		temp->free_entry(false);
	}
}

void huffman_list::remove_second_entry() {
	if (this->list != nullptr) {
		auto temp = this->list->get_next();
		if (temp != nullptr) {
			this->list->set_next(temp->get_next());
			temp->set_next(nullptr);
			temp->free_entry(false);
		}
	}
}

void huffman_list::print() {
	if (this->list != nullptr) {
		huffman_list_entry* curr = list;
		while (curr != nullptr) {
			curr->print();
			curr = curr->get_next();
		}
	}
}