#include <iostream>
#include "week1/task1.h"
#include "week1/task2.h"
#include "week1/task3.h"

int main() {
    int c[7] = {1, 2, 3, 4, 5};
    GeometricVector<int, -1> vec5(c, 5);
    vec5.show();
    vec5.add_element(10);
    vec5.show();
}
