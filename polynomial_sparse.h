#ifndef I_HATE_CPP_POLYNOMIAL_SPARSE_H
#define I_HATE_CPP_POLYNOMIAL_SPARSE_H

#include <initializer_list>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>

template<typename Type>
class PolynomialSparse {
private:
    std::map<int, Type> data_;

    void cut() {
        typename std::map<int, Type>::iterator it = data_.begin();
        while (it != data_.end()) {
            if (it->second == 0) {
                it = data_.erase(it);
            } else {
                it++;
            }
        }
    }

public:
    constexpr PolynomialSparse() {
        data_.insert(std::make_pair(0, 0));
    }

    constexpr PolynomialSparse(const PolynomialSparse<Type> &other) {
        for (const std::pair<int, Type> &element: other.data_) {
            data_.insert(element);
        }
    }

    constexpr PolynomialSparse(const std::initializer_list<std::pair<int, Type>> &list) {
        for (const std::pair<int, Type> &element: list) {
            data_.insert(element);
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const PolynomialSparse<Type> &pol) {
        for (const std::pair<int, Type> element: pol.data_) {
            if (element.second > 0) {
                out << "+";
            }
            out << element.second << "x^" << element.first;
        }
        return out;
    }

    Type &operator[](const unsigned int i) {
        return data_[i];
    }

    const Type &operator[](const unsigned int i) const {
        return data_[i];
    }

    PolynomialSparse<Type> &operator=(const PolynomialSparse<Type> &other) {
        data_.clear();
        for (const std::pair<int, Type> &element: other.data_) {
            data_.insert(element);
        }
        return *this;
    }

    PolynomialSparse<Type> &operator+=(const PolynomialSparse<Type> &other) {
        for (const std::pair<int, Type> &element: other.data_) {
            if (data_.count(element.first)) {
                data_[element.first] += element.second;
            }
            data_.insert(element);
        }
        cut();
        return *this;
    }

    PolynomialSparse<Type> operator+(const PolynomialSparse<Type> &other) const {
        PolynomialSparse<Type> pol_res(*this);
        pol_res += other;
        return pol_res;
    }

    PolynomialSparse<Type> &operator-=(const PolynomialSparse<Type> &other) {
        for (const std::pair<int, Type> &element: other.data_) {
            if (data_.count(element.first)) {
                data_[element.first] -= element.second;
            }
            data_.insert(std::pair<int, Type>{element.first, -element.second});
        }
        cut();
        return *this;
    }

    PolynomialSparse<Type> operator-(const PolynomialSparse<Type> &other) const {
        PolynomialSparse<Type> pol_res(*this);
        pol_res -= other;
        return pol_res;
    }

    PolynomialSparse<Type> &operator*=(const PolynomialSparse<Type> &other) {
        *this = *this * other;
        return *this;
    }

    PolynomialSparse<Type> operator*(const PolynomialSparse<Type> &other) const {
        PolynomialSparse<Type> pol_res;
        for (const std::pair<int, Type> &element1: data_) {
            for (const std::pair<int, Type> &element2: other.data_) {
                pol_res += PolynomialSparse<Type>(
                        {std::pair<int, Type>{element1.first + element2.first, element1.second * element2.second}});
            }
        }
        return pol_res;
    }


    PolynomialSparse<Type> &operator/=(const PolynomialSparse<Type> &other) {
        if (data_.rbegin()->first < other.data_.rbegin()->first) {
            return *this;
        }
        PolynomialSparse<Type> pol_res;
        PolynomialSparse<Type> quotient;
        std::pair<int, Type> mon;
        while (data_.begin() != data_.end() && data_.rbegin()->first >= other.data_.rbegin()->first) {
            mon = {data_.rbegin()->first - other.data_.rbegin()->first,
                   data_.rbegin()->second / other.data_.rbegin()->second};
            quotient = {mon};
            pol_res += quotient;
            *this -= quotient * other;
        }
        *this = pol_res;
        return *this;
    }

    PolynomialSparse<Type> operator/(const PolynomialSparse<Type> &other) const {
        PolynomialSparse<Type> pol_res(*this);
        return pol_res /= other;
    }

    bool operator==(const PolynomialSparse<Type> &other) const {
        return data_ == other.data_;
    }

    PolynomialSparse<Type> differ() const {
        PolynomialSparse<Type> pol_res;
        std::pair<int, Type> mon;
        for (const std::pair<int, Type> &element: data_) {
            if (element.first == 0) {
                continue;
            }
            if (element.first == 1) {
                pol_res[0] = element.second;
                continue;
            }
            mon = {element.first - 1, element.first * element.second};
            pol_res.data_.insert(mon);
        }
        pol_res.cut();
        return pol_res;
    }

    PolynomialSparse<Type> antidiffer() const {
        PolynomialSparse<Type> pol_res;
        std::pair<int, Type> mon;
        for (const std::pair<int, Type> &element: data_) {
            mon = {element.first + 1, element.second / (element.first + 1)};
            pol_res.data_.insert(mon);
        }
        pol_res.cut();
        return pol_res;
    }

    Type operator()(const Type x) const {
        Type res = 0;
        for (const std::pair<int, Type> &mon: data_) {
            res += mon.second * std::pow(x, mon.first);
        }
        return res;
    }

    Type root_newton(Type approx_root, int iterates) const {
        for (int i = 0; i < iterates; i++) {
            approx_root = approx_root - (*this)(approx_root) / (*this).differ()(approx_root);
        }
        return approx_root;
    }

    std::vector<Type> roots(Type a, Type b, int segments, int iterates) {
        std::vector<Type> res;
        res.reserve(segments);
        Type length = (b - a) / segments;
        Type a_it = a;
        Type b_it = a + length;
        if ((*this)(a_it) == 0) {
            res.push_back(a_it);
        }
        for (int i = 0; i <= segments; i++) {
            if ((*this)(a_it) * (*this)(b_it) < 0) {
                res.push_back(root_newton((a_it + b_it) / 2, iterates));
            } else if ((*this)(b_it) == 0) {
                res.push_back(b_it);
            }
            a_it = b_it;
            b_it += length;
        }
        return res;
    }
};

#endif //I_HATE_CPP_POLYNOMIAL_SPARSE_H
