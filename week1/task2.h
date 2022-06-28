#ifndef I_HATE_CPP_TASK2_H
#define I_HATE_CPP_TASK2_H

#endif //I_HATE_CPP_TASK2_H

template<unsigned int N>
constexpr unsigned int factorial() {
    return N * factorial<N - 1>();
}

template<>
constexpr unsigned int factorial<0>() {
    return 1;
}