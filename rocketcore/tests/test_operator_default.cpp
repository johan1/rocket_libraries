#include "../src/OperatorDefault.h"

#include <iostream>

class A {
public:
    A() : a(0) {}

    A(int a) : a(a) {}

    friend bool operator==(A const& a1, A const& a2) {
        std::cout << "Specialized ==" << std::endl;
        return a1.a == a2.a;
    }

    friend bool operator<(A const& a1, A const & a2) {
        std::cout << "Specialized <" << std::endl;
        return a1.a < a2.a;
    }

private:
    int a;
};

int main() {
    A a1 = 5;
    A a2 = 4;

    a1 == a2;
    a1 != a2;
    a1 < a2;
    a1 <= a2;
    a1 > a2;
    a2 >= a2;

    return 0;
}

