#include "text_coder.h"
#include <iostream>

namespace huff {
	text_coder::text_coder() {
	}

	text_coder::~text_coder() {
	}

	void text_coder::encryption(std::string filename) {
		std::string temp_str;
		huff::freq_table freq_tab;
		freq_tab.create_freq_table(filename);

		huff::huffman_list huff_list;
		huff_list.create_huffman_list(freq_tab);
		huff_list.print_huffman_list();
		huff_list.create_huffman_tree();

		huff::coding_table cod_table = huff_list.create_coding_table();
		temp_str = freq_tab.get_stream();
		
		for (size_t i = 0; i < temp_str.length(); i++) {
			for (size_t j = 0; j < cod_table.get_size(); j++) {
				if (cod_table.get_entry(j).get_c() == temp_str[i]) {
					encrypted_str += cod_table.get_entry(j).get_code();
					break;
				}
			}
		}
		print_huffman_results(freq_tab, huff_list, cod_table);
	}


	void text_coder::print_huffman_results(freq_table &freq_tab, huffman_list &huff_list, coding_table &cod_table) {

		std::cout << "--FREQUENCY TABLE--------------------" << "\n";
		freq_tab.print_freq_table();
		std::cout << "\n";
		std::cout << "--HUFFMAN TREE-----------------------" << "\n";
		huff_list.print_huffman_list();
		std::cout << "\n";
		std::cout << "--CODING TABLE-----------------------" << "\n";
		cod_table.print_coding_table();
		std::cout << "\n";
		std::cout << "--ENCRYPTED STRING-----------------------" << "\n";
		std::cout << encrypted_str << "\n";
	}

	void text_coder::decryption(std::string filename) {
		if (encrypted_str == "\0") {
			std::cout << "ERROR" << "\n";
		}
		else {
			huff::freq_table freq_tab;
			freq_tab.create_freq_table(filename);

			huff::huffman_list huff_list;
			huff_list.create_huffman_list(freq_tab);
			huff_list.create_huffman_tree();

			huff::coding_table cod_table = huff_list.create_coding_table();

			std::string temp_str;
			std::string decrypted_str;
			for (size_t i = 0; i < encrypted_str.length(); i++) {
				temp_str = encrypted_str[i];
				for (size_t j = 0; j < cod_table.get_size(); j++) {
					if (cod_table.get_entry(j).get_code() == temp_str) {
						decrypted_str += cod_table.get_entry(j).get_c();
						temp_str = "";
						break;
					}
				}
			}
			std::cout << decrypted_str << "\n";
		}
	}
}