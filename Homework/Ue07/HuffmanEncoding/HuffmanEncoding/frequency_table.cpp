#include <iostream>
#include "frequency_table.h"

frequency_table_entry::frequency_table_entry(const char car, const int p, const int c) {
	this->character = car;
	this->frequency = p;
	this->count = c;
}

void frequency_table_entry::update_frequency(const double total) {

	double h1 = this->count / total;
	int fr = (int)(h1 * 100);
	this->frequency = (int)((this->count / total) * 100);
}

void frequency_table_entry::add_to_char(const int c) {
	this->count += c;
}

bool frequency_table_entry::is_character(const char car) {
	return car == this->character;
}

void frequency_table_entry::new_char(const char car, const int c) {
	this->character = car;
	this->count = c;
	this->frequency = 0;
}

void frequency_table_entry::print() {
	std::cout << "Char: " << this->character << ", Freq: " << this->frequency << "\n";
}

char frequency_table_entry::get_character() {
	return this->character;
}

int frequency_table_entry::get_frequency() {
	return this->frequency;
}

// ### Frequency Table ### //

frequency_table::frequency_table(const int len) {
	this->table = new frequency_table_entry[len];
	this->length = len;
	this->total = 0;
}

void frequency_table::add_character(const char car) {
	bool found = false;
	for (int i = 0; i < this->length; i++) {
		if (table[i].is_character(car)) {
			table[i].add_to_char();
			total++;
			table[i].update_frequency(this->total);
			found = true;
			break;
		}
	}

	if (!found) {
		for (int i = 0; i < this->length; i++) {
			if (table[i].is_character('\0')) {
				table[i].new_char(car, 1);
				total++;
				table[i].update_frequency(this->total);
				break;
			}
		}
	}
}

void frequency_table::update_table() {
	for (int i = 0; i < this->length; i++) {
		table[i].update_frequency(this->total);
	}
}

void frequency_table::print() {
	for (int i = 0; i < this->length; i++) {
		if (!table[i].is_character('\0'));
			table[i].print();
	}
}

int frequency_table::get_length() {
	return this->length;
}

frequency_table_entry* frequency_table::get_table() {
	return this->table;
}