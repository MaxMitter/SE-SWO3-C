#include <stdlib.h>

#include "deque.h"
#include "deque.cpp"

int main() {
	//swo::deque<int> i{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	//swo::deque<std::string> d{ "this", "is", "a", "very", "important", "Test" };
	swo::deque<std::string> d(3, "test");
	//swo::deque<std::string> f{ d };
	//i.print();
	d.print();
	//f.print();

	d.push_front("test2");
	d.push_front("test2");
	d.push_front("test2");
	d.push_front("test2");
	d.push_front("test2");
	d.print();
}