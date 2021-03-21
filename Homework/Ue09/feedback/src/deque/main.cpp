#include "deque.hpp"
#include <iostream>
#include <numeric> //for accumulate
#include <algorithm> //for max_element

template<typename Type>
void print(swo::deque<Type>& d) {
    for (const auto& val : d) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}
template<typename Type>
void print_reverse(swo::deque<Type>& d) {
    auto rbegin{d.end()};
    auto rend{d.begin()};
    for (; rbegin != rend; ) {
        std::cout << *(--rbegin) << " ";
    }
    std::cout << "\n";
}

int main () {
    std::cout << "init d1 with init list: ";
    for (int n : {23, 38, 14, -3, 1, 14, 9, 103, -56, 0}) {
        std::cout << n << ' ';
    }
    std::cout << "\n";
    swo::deque<int> d1{23, 38, 14, -3, 1, 14, 9, 103, -56, 0};

    std::cout << "size of d1: " << d1.size() << "\n";

    std::cout << std::boolalpha << "d1 empty?: " << d1.empty() << "\n";

    std::cout << "print d1: ";
    print(d1);

    std::cout << "print d1 reverse: ";
    print_reverse(d1);

    std::cout << "\n\n";

    std::cout << "resize to 15 elements and print: ";
    print(d1);
    std::cout << "size of d1: " << d1.size() << "\n";

    std::cout << "resize to 20 elements with value 2 and print: ";
    d1.resize(20, 2);
    print(d1);

    std::cout << "resize to 5 elements and print: ";
    d1.resize(5);
    print(d1);

    std::cout << "\n\n";

    std::cout << "construct d2 with d1 and print: ";
    swo::deque d2{d1};
    print(d2);

    std::cout << "push back two values and print: ";
    d2.push_back(33);
    d2.push_back(43);
    print(d2);

    std::cout << "push front two values and print: ";
    d2.push_front(12);
    d2.push_front(15);
    print(d2);

    std::cout << "pop front and back and print: ";
    d2.pop_front();
    d2.pop_back();
    print(d2);

    std::cout << "front is: ";
    std::cout << d2.front() << "\n";

    std::cout << "back is: ";
    std::cout << d2.back() << "\n";

    std::cout << "d2 summed up is: " << std::accumulate(d2.begin(), d2.end(), 0) << "\n";

    std::cout << "d2 multiplied up is: " << std::accumulate(d2.begin(), d2.end(), 1, std::multiplies<>()) << "\n";

    std::cout << "max from d2 is: " << *std::max_element(d2.begin(), d2.end()) << "\n";

    std::cout << "\n\n";

    std::cout << "push front two values into d1 and d2 and print:\n";
    d1.push_front(55);
    d1.push_front(66);
    d2.push_front(55);
    d2.push_front(66);
    std::cout << "print d1: ";
    print(d1);
    std::cout << "print d2: ";
    print(d2);
    std::cout << "d1 < d2?: " << std::boolalpha << (d1 < d2) << "\n";
    std::cout << "d1 == d2?: " << std::boolalpha << (d1 == d2) << "\n";
    std::cout << "d1 <= d2?: " << std::boolalpha << (d1 <= d2) << "\n";
    std::cout << "d1 > d2?: " << std::boolalpha << (d1 > d2) << "\n";
    std::cout << "d1 != d2?: " << std::boolalpha << (d1 != d2) << "\n";
    std::cout << "d1 >= d2?: " << std::boolalpha << (d1 >= d2) << "\n";

    std::cout << "\n";

    std::cout << "d1[3] = " << d1[3] << "\n\n";

    std::cout << "construct d3 with {10, 5} and print: ";
    swo::deque<int> d3{10, 5};
    print(d3);

    std::cout << "construct d4 with (10, 5) and print: ";
    swo::deque<int> d4(10, 5);
    print(d4);

    std::cout << "construct d5 with (10) and print: ";
    swo::deque<int> d5(10);
    print(d5);


	
}