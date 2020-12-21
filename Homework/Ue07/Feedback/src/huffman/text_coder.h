#pragma once
#include <string>
#include "freq_table.h"
#include "huffman_list.h"
#include "coding_table.h"

namespace huff {
	class text_coder {
	public:
		text_coder();
		~text_coder();

		void encryption(std::string filename);
		void decryption(std::string filename);

	private:
		void print_huffman_results(freq_table& freq_tab, huffman_list& huff_list, coding_table& cod_table) ;
		std::string encrypted_str{ '\0' };
	};
}