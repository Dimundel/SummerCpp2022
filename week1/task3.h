#ifndef I_HATE_CPP_TASK3_H
#define I_HATE_CPP_TASK3_H

#endif //I_HATE_CPP_TASK3_H

#include <cmath>
#include <vector>

template<typename T, int N>
class GeometricVector {
private:
    T *column;
    double length;
public:
    GeometricVector() {
        column = nullptr;
        length = 0;
    }

    GeometricVector(T *column) {
        this->column = column;
        double length_square = 0;
        for (int i = 0; i < N; i++) {
            length_square += pow(column[i], 2);
        }
        this->length = sqrt(length_square);
    }

    void show() {
        for (int i = 0; i < N; i++) {
            std::cout << column[i] << std::endl;
        }
    }

    double get_length() {
        return length;
    }

    GeometricVector<T, N> operator+(GeometricVector<T, N> v2) {
        T res_column[N];
        for (int i = 0; i < N; i++) {
            res_column[i] = column[i] + v2.column[i];
        }
        GeometricVector<T, N> res_v(res_column);
        return res_v;
    }

    template<typename P>
    GeometricVector<T, N> operator*(P num) {
        T res_column[N];
        for (int i = 0; i < N; i++) {
            res_column[i] = column[i] * num;
        }
        GeometricVector<T, N> res_v(res_column);
        return res_v;
    }

    template<typename P>
    friend GeometricVector<T, N> operator*(P num, GeometricVector<T, N> v) {
        T res_column[N];
        for (int i = 0; i < N; i++) {
            res_column[i] = v.column[i] * num;
        }
        GeometricVector<T, N> res_v(res_column);
        return res_v;
    }

    GeometricVector<T, N> operator-(GeometricVector<T, N> v2) {
        T res_column[N];
        for (int i = 0; i < N; i++) {
            res_column[i] = column[i] - v2.column[i];
        }
        GeometricVector<T, N> res_v(res_column);
        return res_v;
    }

    bool operator>(GeometricVector<T, N> v2) {
        return (length > v2.length);
    }

    bool operator<(GeometricVector<T, N> v2) {
        return (length < v2.length);
    }

    bool operator==(GeometricVector<T, N> v2) {
        return (length == v2.length);
    }

    void operator=(GeometricVector<T, N> v2) {
        for (int i = 0; i < N; i++) {
            column[i] = v2.column[i];
        }
    }
};

template<typename T>
class GeometricVector<T, -1> {
private:
    std::vector<T> column;
    double length;
public:
    GeometricVector(T *column, unsigned int N) {
        for (int i = 0; i < N; i++) {
            this->column.push_back(column[i]);
        }
        double length_square = 0;
        for (int i = 0; i < N; i++) {
            length_square += pow(column[i], 2);
        }
        this->length = sqrt(length_square);
    }

    double get_length() {
        return length;
    }

    unsigned int get_size() {
        return column.size();
    }

    void show() {
        for (int i = 0; i < column.size(); i++) {
            std::cout << column[i] << std::endl;
        }
    }

    void add_element(T num) {
        column.push_back(num);
    }
};