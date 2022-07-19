#include <iostream>
#include "week1/task1.h"
#include "week1/task2.h"
#include "week1/task3.h"
#include "polynomial.h"

int main() {
    std::pair<int, float> mon1{0, 6}, mon2{1, 11}, mon3{2, 6}, mon4{3, 1}, mon5{0, 1}, mon6{1, 1};
    const PolynomialSparse<float> pol1{mon1, mon2, mon3, mon4}, pol2{mon5, mon6};
    pol1*pol2;
}

