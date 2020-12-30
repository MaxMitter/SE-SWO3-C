#include <iostream>

struct error {
	explicit error(const std::string &msg) : m_msg{msg} {}

	std::string m_msg;
};

static void foo() {
	std::cout << "before error in foo\n";

	//throw 1;
	//throw "A severe error occurred\n";
	throw error("Some Error");
	std::cout << "after error in foo\n";
}

int main() {
	try {
		foo();
	}
	catch (error err) {
		std::cout << err.m_msg << std::endl;
	}
	catch (int err_code) {
		std::cout << "error_code: " << err_code << std::endl;
	}
	catch (const char* error_message) {
		std::cout << error_message;
	}
}