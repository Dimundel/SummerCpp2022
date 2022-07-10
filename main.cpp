#include <iostream>
#include "week1/task1.h"
#include "week1/task2.h"
#include "week1/task3.h"

int main() {
    Vector<float, 3> v1{1, 2, 3};
    Vector<float, 3> v2{5, -2, 1};

    std::cout << v1 << v1 + v2 << v1 - v2 << v1 * 2 << 2 * v1 << v1 / 2 << v1.norm() << std::endl;

    v1 *= 2;

    std::cout << v1;

    Vector<float, -1> v3{1, 1, 3, 5};
    Vector<float, -1> v4{1, 0, 3, 5};

    std::cout << v3 + v4 << v3 * 2 << v3.norm() << std::endl;

    v3 += v4;

    std::cout << v3 / 2;
}

