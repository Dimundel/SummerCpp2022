#include <iostream>
#include "week1/task1.h"
#include "week1/task2.h"
#include "week1/task3.h"

int main() {
    int a[3] = {2, 3, 5};
    int b[3] = {3, 0, 0};
    GeometricVector<int, 3> vec1(a);
    GeometricVector<int, 3> vec2(b);
    vec1.show();
    vec2.show();
    //GeometricVector<int, 3> vec3 = vec1 + vec2;
    //vec3.show();
    //GeometricVector<int, 3> vec4 = vec1-vec2;
    //vec4.show();
    std::cout << vec1.get_length() << std::endl;
    std::cout << vec2.get_length() << std::endl;
    if (vec2 > vec1) {
        std::cout << "vec2 > vec1";
    }
    vec1 = vec2;
    vec1.show();
    return 0;
}
