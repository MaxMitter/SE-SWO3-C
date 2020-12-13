#include <iostream>
#include <iomanip>
#include "tables.h"

frequency_table_entry::frequency_table_entry(const char car, const double p, const int c) {
	this->character = car;
	this->frequency = p;
	this->count = c;
}

void frequency_table_entry::update_frequency(const double total) {
	this->frequency = (this->count / total) * 100;
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
	this->frequency = 0.0;
}

void frequency_table_entry::print() {
	std::cout << this->character << " | "
			  << this->frequency
			  << "% | Count: " << this->count << "\n";
}

char frequency_table_entry::get_character() {
	return this->character;
}

double frequency_table_entry::get_frequency() {
	return this->frequency;
}


// ### Frequency Table ### //

frequency_table::frequency_table(const int len) {
	this->table = new frequency_table_entry[len];
	this->length = len;
	this->total = 0;
}

frequency_table::~frequency_table() {
	if (this->table != nullptr)
		delete[] this->table;
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
		if (!table[i].is_character('\0'))
			table[i].print();
	}
}

int frequency_table::get_length() {
	return this->length;
}

frequency_table_entry* frequency_table::get_table() {
	return this->table;
}


// ### Coding Table Entry ### //

coding_table_entry::coding_table_entry() {
	this->character = '\0';
	this->code = "";
}

coding_table_entry::coding_table_entry(char car, std::string code) {
	this->character = car;
	this->code = code;
}

std::string coding_table_entry::get_code() {
	return this->code;
}

void coding_table_entry::set_code(std::string code) {
	this->code = code;
}

char coding_table_entry::get_character() {
	return this->character;
}

void coding_table_entry::set_char(char car) {
	this->character = car;
}

void coding_table_entry::print() {
	std::cout << "C: " << this->character << ", Code: " << this->code << std::endl;
}


// ### Coding Table ### //

coding_table::coding_table(int size) {
	this->table = new coding_table_entry[size];
	this->size = size;
}

coding_table::~coding_table() {
	if (this->table != nullptr)
		delete[] this->table;
}

void coding_table::add_entry(char car, std::string code) {
	for (int i = 0; i < this->size; i++) {
		char cur_char = this->table[i].get_character();
		if (cur_char == car || cur_char == '\0') {
			table[i].set_char(car);
			table[i].set_code(code);
			break;
		}
	}
}

void coding_table::print() {
	for (int i = 0; i < this->size; i++) {
		this->table[i].print();
	}
}

std::string coding_table::get_code(char car) {
	for (int i = 0; i < this->size; i++) {
		if (this->table[i].get_character() == car)
			return this->table[i].get_code();
	}

	std::cout << "Entry " << car <<" not found in coding table, aborting...";
	exit(-1);
}

char coding_table::get_character(std::string code) {
	for (int i = 0; i < this->size; i++) {
		if (this->table[i].get_code() == code)
			return this->table[i].get_character();
	}

	std::cout << "Entry " << code << " not found in coding table, aborting...";
	exit(-1);
}

bool coding_table::is_valid_code(std::string code) {
	for (int i = 0; i < this->size; i++) {
		if (this->table[i].get_code() == code)
			return true;
	}

	return false;
}