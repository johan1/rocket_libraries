#include "../src/OperatorDefault.h"

#include <iostream>

class A : public strict_totally_ordered<A> {
public:
    A() : a(0) {}

    A(int a) : a(a) {}
/*
    friend bool operator==(A const& a1, A const& a2) {
        std::cout << "Specialized ==" << std::endl;
        return a1.a == a2.a;
    }
*/

    friend bool operator<(A const& a1, A const & a2) {
//        std::cout << "Specialized <" << std::endl;
        return a1.a < a2.a;
    }

private:
    int a;
};

void test(A const& a1, A const& a2) {
	std::cout << "(a1 < a2) " << (a1 < a2) << "\n";
	std::cout << "(a1 <= a2) " << (a1 <= a2) << "\n";
	std::cout << "(a1 == a2) " << (a1 == a2) << "\n";
	std::cout << "(a1 >= a2) " << (a1 >= a2) << "\n";
	std::cout << "(a1 > a2) " << (a1 > a2) << "\n";
	std::cout << "(a1 != a2) " << (a1 != a2) << "\n";
}

int main() {
    A a1 = 5;
    A a2 = 4;
	std::cout << "Testing a1 > a2" << std::endl;
	test(a1, a2);
	std::cout << "Testing a1 == a1" << std::endl;
	test(a1, a1);
	std::cout << "Testint a1 < a2" << std::endl;
	test(a2, a1);
}

