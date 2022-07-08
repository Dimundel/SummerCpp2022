#include <iostream>
#include "week1/task1.h"
#include "week1/task2.h"
#include "week1/task3.h"

int main() {
    for (const auto &element: terribleTrigonometry(4)){
        std::cout << element.x << " " << element.y << std::endl;
    }
}
