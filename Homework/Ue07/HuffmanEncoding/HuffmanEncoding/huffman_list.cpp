#include <iostream>
#include "huffman_list.h"

huffman_list_entry::huffman_list_entry(const char car, const int p) {
	this->character = car;
	this->frequency = p;
	this->next = nullptr;
}

void huffman_list_entry::set_next(huffman_list_entry* entry) {
	this->next = entry;
}

bool huffman_list_entry::has_next() {
	return this->next != nullptr;
}

huffman_list_entry* huffman_list_entry::get_next() {
	return this->next;
}

bool huffman_list_entry::frequency_is_bigger_than(const huffman_list_entry other) {
	return (this->frequency > other.frequency);
}

bool huffman_list_entry::operator< (huffman_list_entry other) {
	return this->frequency < other.frequency;
}

bool huffman_list_entry::operator> (huffman_list_entry other) {
	return this->frequency > other.frequency;
}

void huffman_list_entry::print() {
	std::cout << "C: " << this->character << ", P: " << this->frequency << '\n';
}


// ### Huffman List ### //

huffman_list::huffman_list() {
	this->list = nullptr;
}

huffman_list::huffman_list(frequency_table freq_table) {
	frequency_table_entry* table = freq_table.get_table();
	this->list = nullptr;
	for (int i = 0; i < freq_table.get_length(); i++) {
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
			if (*curr < *entry) {
				prev = curr;
				curr = curr->get_next();
			}
			else
				break;
		}

		if (!curr->has_next()) {
			if (*curr < *entry)
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

void huffman_list::print() {
	if (this->list != nullptr) {
		huffman_list_entry* curr = list;
		while (curr != nullptr) {
			curr->print();
			curr = curr->get_next();
		}
	}
}