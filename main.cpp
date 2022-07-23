#include <iostream>
#include "week1/task1.h"
#include "week1/task2.h"
#include "week1/task3.h"
#include "polynomial.h"

int main() {
    std::pair<int, float> mon1{0, 10}, mon2{2, -5}, mon3{3, 1};
    PolynomialSparse<float> pol1{mon1, mon2, mon3};
    std::cout << pol1.root(3, 10);
}

