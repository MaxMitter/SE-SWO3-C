#include <algorithm>
#include "deque.h"

using namespace swo;
using namespace std;

void test_swap() {
	deque<int> i = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	deque<int> test = { 0, 1, 2, 3, 4 };

	cout << "Test before swap" << endl;
	i.print();
	test.print();

	i.swap(test);
	cout << "Test after swap" << endl;
	i.print();
	test.print();

	cout << "Test assignment operator copy: " << endl;
	test = i;
	i.print();
	test.print();

	cout << "Test assignment operator move: " << endl;
	test = std::move(i);
	i.print();
	test.print();
}

void test_iterator() {
	deque<int> d = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	cout << "Test iterator ++: " << endl;
	deque<int>::iterator it = d.begin();
	
	while (it <= d.end()) {
		cout << *it << " | ";
		++it;
	}

	cout << endl << "Test iterator --: " << endl;
	deque<int>::iterator it2 = d.end();	
	while (it2 >= d.begin()) {
		cout << *it2 << " | ";
		--it2;
	}

	cout << endl;
}

void test_iterator_range_based_for() {
	deque<int> i = { 1, 2, 3, 4, 5, 6 };

	cout << "Test iterator range based for" << endl;
	
	for (auto it : i) {
		cout << it << " | ";
	}

	cout << endl;
}

void test_operator() {
	deque<int> const d = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	deque<int> const f = { 1, 2, 3, 4, 5 };
	deque<int> const g = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	deque<int> const d2 = d;

	deque<char> const c1 = { 'a', 'b', 'c', 'd', 'e' };
	deque<char> const c2 = { 'a', 'b', 'c', 'e' };

	cout << std::boolalpha;
	cout << "d == f: " << (d == f) << endl;
	cout << "d == g: " << (d == g) << endl;
	cout << "d == d2: " << (d == d2) << endl;
	cout << "========================================" << endl;
	cout << "d != f: " << (d != f) << endl;
	cout << "d != g: " << (d != g) << endl;
	cout << "d != d2: " << (d != d2) << endl;


	cout << "========================================" << endl;
	cout << "d < f: " << (d < f) << endl;
	cout << "d < g: " << (d < g) << endl;
	cout << "d < d2: " << (d < d2) << endl;
	cout << "c1 < c2: " << (c1 < c2) << endl;

	cout << "========================================" << endl;
	cout << "d <= f: " << (d <= f) << endl;
	cout << "d <= g: " << (d <= g) << endl;
	cout << "d <= d2: " << (d <= d2) << endl;
	cout << "c1 <= c2: " << (c1 <= c2) << endl;

	cout << "========================================" << endl;
	cout << "d > f: " << (d > f) << endl;
	cout << "d > g: " << (d > g) << endl;
	cout << "d > d2: " << (d > d2) << endl;
	cout << "c1 > c2: " << (c1 > c2) << endl;
	
	cout << "========================================" << endl;
	cout << "d >= f: " << (d >= f) << endl;
	cout << "d >= g: " << (d >= g) << endl;
	cout << "d >= d2: " << (d >= d2) << endl;
	cout << "c1 >= c2: " << (c1 >= c2) << endl;
}

void test_constructor() {
	deque<std::string> test1 = { "this", "is", "a", "test", "string" };
	deque<std::string> test2;

	test1.print();
	test2.print();

	test2 = test1;
	test1.print();
	test2.print();

	test2 = std::move(test1);
	test1.print();
	test2.print();

	deque<int> test3(5, 10);
	deque<int> test4(20);

	test3.print();
	test4.print();
}

void test_deque_of_deque() {
	deque<int> t1 = { 1 };
	deque<int> t2 = { 2 };
	deque<int> t3 = { 3 };
	deque<int> t4 = { 4 };
	deque<deque<int>> d_of_d = { t1, t2 };

	d_of_d.push_front(t3);
	d_of_d.push_front(t4);

	d_of_d.print();

	d_of_d.pop_back();
	d_of_d.print();
}

void test_push() {
	deque<int> i = { 1, 2, 3, 4, 5, 6 };

	i.print();

	i.push_front(1);
	i.push_back(7);

	i.print();
}

int main() {
	//test_swap();
	//test_iterator();
	//test_operator();
	//test_constructor();
	test_deque_of_deque();
	//test_iterator_range_based_for();
	//test_push();
}