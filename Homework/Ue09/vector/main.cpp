#include <iostream>
#include <string>

#include "vector1.h"
#include "vector2.h"
#include "algorithms.h"

using namespace std::string_literals;

static void test_vector1() {
	swo::vector1<std::string> v1{ 2 };

	v1.push_back("Hagenberg");
	v1.push_back("Linz");

	std::cout << "v1.size() = " << v1.size() << "; v1.capacity() = " << v1.capacity() << std::endl;

	v1.push_back("Wien"s);
	v1.push_back("New York"s);
	v1.push_back("Afisl"s);

	std::cout << "v1.size() = " << v1.size() << "; v1.capacity() = " << v1.capacity() << std::endl;

	print(v1) << std::endl;

	swo::vector1<std::string> v2{ v1 };

	swo::vector1<std::string> v3{ std::move(v2) };
}

static void test_iterator() {
	int array[]{ 0,1,2,3,4 };
	int* begin = array;
	int* end = array + sizeof(array) / sizeof(array[0]);

	for (int* ptr = begin; ptr != end; ++ptr) {
		std::cout << *ptr << " ";
	}
	std::cout << "\n";

	swo::vector2<std::string> v{ "Hagenberg"s, "Linz"s, "Wien"s };

	for (swo::vector2<std::string>::iterator it = v.begin(); it != v.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\n";

	for (std::string s : v)
		std::cout << s << " ";
	std::cout << "\n";
	//swo::vector2<std::string>::iterator it;
}

static bool is_even(int n) {
	return n % 2 == 0;
}

static void multiply_by_2(int& n) {
	n *= 2;
}

class multiplier {
public:
	multiplier(int factor) : m_factor{ factor } {

	}

	void operator() (int& n) {
		n *= m_factor;
	}

private:
	int m_factor;
};

static void test_algorithmns() {
	int array[]{ 0,1,2,3,4 };
	int* begin = array;
	int* end = array + sizeof(array) / sizeof(array[0]);

	swo::print(begin, end) << std::endl;

	swo::for_each_if_ptr(begin, end, is_even, multiply_by_2);

	std::cout << "----------------------------------------\n";

	swo::vector2<int> v{0, 1, 2, 3, 4, 5, 6};
	swo::print(v.begin(), v.end()) << std::endl;

	swo::for_each_if_ptr(v.begin(), v.end(), is_even, multiply_by_2);
	swo::print(v.begin(), v.end()) << std::endl;

	swo::for_each_if_ptr(v.begin(), v.end(), is_even, multiplier{ 3 });
	swo::print(v.begin(), v.end()) << std::endl;

	int factor = 10;
	swo::for_each_if_ptr(v.begin(), v.end(), [](int n) { return n % 2 != 0; }, [factor](int& n) { n *= factor; });
	swo::print(v.begin(), v.end()) << std::endl;
}

int main() {

	try {
		std::cout << "======= test_vector1 =======" << std::endl;
		test_vector1();
		std::cout << "============================" << std::endl;

		std::cout << "======= test_vector1 =======" << std::endl;
		test_iterator();
		std::cout << "============================" << std::endl;

		std::cout << "======= test_algorithmns =======" << std::endl;
		test_algorithmns();
		std::cout << "============================" << std::endl;

	}
	catch (std::exception& ex) {
		std::cout << "EXCEPTION: " << ex.what() << "!" << std::endl;
	}

}