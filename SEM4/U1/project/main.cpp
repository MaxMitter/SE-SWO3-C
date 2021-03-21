#include <vector>
#include <iostream>
#include <iterator>

int main() {
	std::ostream_iterator<int> osi{ std::cout };

	std::vector v{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	/*for (auto& i : v) {
		std::cout << i << ", ";
	}*/

	auto const end{ std::remove_if(std::begin(v), std::end(v), [](int const x) {
		return x % 2 == 0;
	}) };
	
	std::copy(std::begin(v), std::end(v), osi); std::cout << "\n";
	
	std::remove(std::begin(v), std::end(v), 5);

	std::copy(std::begin(v), std::end(v), osi); std::cout << "\n";
}