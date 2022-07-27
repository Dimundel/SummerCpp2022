#include <iostream>
#include "week1/task1.h"
#include "week1/task2.h"
#include "week1/task3.h"
#include "polynomial.h"

int main() {
    Polynomial<float> pol1{0, 0, 0, 3, -4, 1};
    for (const auto &root: pol1.roots(-3, 3, 100, 100)) {
        std::cout << root << " ";
    }
}

