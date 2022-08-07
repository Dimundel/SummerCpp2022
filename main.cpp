#include <iostream>
#include "week1/task1.h"
#include "week1/task2.h"
#include "week1/task3.h"
#include "polynomial.h"
#include "polynomial_sparse.h"

int main() {
    Polynomial<float> pol1{1, 0, -2, 0, 1};
    for (const auto &root: pol1.roots(-3, 3, 100, 10)) {
        std::cout << root << " ";
    }
    std::pair<int, float> mon1{0, 2}, mon2{1, 5}, mon3{2, -3};
    PolynomialSparse<float>{mon1, mon2, mon3};
}

