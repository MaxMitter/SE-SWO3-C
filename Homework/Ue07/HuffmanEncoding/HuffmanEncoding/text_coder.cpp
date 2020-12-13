#include "text_coder.h"
#include <iostream>
#include <chrono>

text_coder::text_coder() {
	this->token = nullptr;
}

text_coder::text_coder(string text) {
	this->token = new coding_token(text);
}

text_coder::~text_coder() {
	if (this->token != nullptr)
		delete this->token;
}

void text_coder::set_text(string text) {
	if (this->token != nullptr) {
		delete this->token;
		this->token = nullptr;
	}

	this->token = new coding_token(text);
}

bool text_coder::encode() {
	if (this->token == nullptr) {
		std::cout << "No Text defined to encode!" << std::endl;
	} else {
		if (this->token->text_empty())
			std::cout << "No Text defined to encode!" << std::endl;
		else {
			auto start = std::chrono::high_resolution_clock::now();
			string encoded = this->token->encode();
			if (!encoded.empty())
				std::cout << "Encoding successfull!" << std::endl;
			else {
				std::cout << "Unexpected error while encoding, aborting." << std::endl;
				return false;
				exit(EXIT_FAILURE);
			}

			auto end = std::chrono::high_resolution_clock::now();
			auto time_taken = end - start;
			auto ms = time_taken / std::chrono::milliseconds(1);
			auto sec = floor(ms / 1000);
			ms -= sec * 1000;
			auto min = floor(sec / 1000);
			sec -= min * 60;
			std::cout << "Encoding took " << min << ":" << sec << "." << ms << " minutes." << std::endl;
			return true;
		}
	}

	return false;
}

bool text_coder::decode() {
	if (this->token == nullptr) {
		std::cout << "No Text defined to encode!" << std::endl;
		return false;
	}
	else {
		auto start = std::chrono::high_resolution_clock::now();
		this->token->decode();

		auto end = std::chrono::high_resolution_clock::now();
		auto time_taken = end - start;
		auto ms = time_taken / std::chrono::milliseconds(1);
		auto sec = floor(ms / 1000);
		ms -= sec * 1000;
		auto min = floor(sec / 1000);
		sec -= min * 60;
		std::cout << "Encoding took " << min << ":" << sec << "." << ms << " minutes." << std::endl;
		return true;
	}
}


void text_coder::print_type(DataType type) {
	switch (type) {
		case frequency_table:
			this->token->print_freq_table();
			break;
		case huffman_list:
			this->token->print_list();
			break;
		case huffman_tree:
			this->token->print_tree();
			break;
		case coding_table:
			this->token->print_coding_table();
			break;
		case texts:
			this->token->print_texts();
			break;
		case size_difference:
			this->token->print_size_difference();
			break;
		default:
			std::cout << "Cannot print Data: DataType not found." << std::endl;
			break;
	}
}