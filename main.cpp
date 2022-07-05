#include <iostream>
#include "week1/task1.h"
#include "week1/task2.h"
#include "week1/task3.h"

int main() {
    Vector<float, 2> a{5, 15};
    Vector<float, 2> b{3, 4};
    Vector<float, 5> n{};
    std::cout << n << a + b << a - b << b * 2 << a / 5 << b.norm() << std::endl;

    b[0] = 5;
    std::cout << b;

    Vector<float, -1> c{1, 2, 3};
    Vector<float, -1> d{};
    Vector<float, -1> e{2, -4, 1};
    std::cout << d << c + e << c - e << c * 2 << e / 2 << e.norm() << std::endl;

    c[1] = 10;
    std::cout << c;

    std::cout << e[2] << std::endl;

    c *= 2;
    std::cout << c;

    c+= e;
    std::cout << c;
}
