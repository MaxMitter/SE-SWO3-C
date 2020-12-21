#include "text_coder.h"
#include <iostream>


void test_encryption(std::string filename) {
	huff::text_coder tc;
	tc.encryption(filename);
}

void test_decryption(std::string filename) {
	huff::text_coder tc;
	tc.decryption(filename);
}

int main() {
	std::cout << "--ENCRYPTION-------------------------------------------" << "\n";
	test_encryption("C:\\Users\\maxmi\\Documents\\FH\\SWO\\c-code\\Homework\\Ue07\\Feedback\\src\\Feedback\\Debug\\test3.txt");

	std::cout << "\n";
	std::cout << "--DECRYPTION-------------------------------------------" << "\n";
	test_decryption("C:\\Users\\maxmi\\Documents\\FH\\SWO\\c-code\\Homework\\Ue07\\Feedback\\src\\Feedback\\Debug\\test3.txt");

	return 0;
}
