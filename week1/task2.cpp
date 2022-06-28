template<unsigned int N>
constexpr unsigned int factorial() {
    return N * factorial<N - 1>();
}

template<>
constexpr unsigned int factorial<0>() {
    return 1;
}