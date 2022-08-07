#ifndef I_HATE_CPP_POLYNOMIAL_H
#define I_HATE_CPP_POLYNOMIAL_H

#include <initializer_list>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>

template<typename Type>
class Polynomial {
private:
    std::vector<Type> data_;

    void cut() {
        while (data_.back() == 0) {
            data_.pop_back();
        }
    }

public:
    constexpr Polynomial() {
        data_ = {0};
    }

    constexpr Polynomial(const Polynomial<Type> &other) {
        data_.reserve(other.data_.size());
        for (const Type &element: other.data_) {
            data_.push_back(element);
        }
    }

    constexpr Polynomial(const std::initializer_list<Type> &list) {
        data_.reserve(list.size());
        for (const Type &element: list) {
            data_.push_back(element);
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const Polynomial<Type> &pol) {
        out << "(";
        for (int i = 0; i < pol.data_.size() - 1; i++) {
            out << pol.data_[i] << ", ";
        }
        out << pol.data_.back() << ")";
        return out;
    }

    Type &operator[](const unsigned int i) {
        return data_[i];
    }

    const Type &operator[](const unsigned int i) const {
        return data_[i];
    }

    Polynomial<Type> &operator=(const Polynomial<Type> &other) {
        data_.resize(other.data_.size());
        for (int i = 0; i < data_.size(); i++) {
            data_[i] = other.data_[i];
        }
        return *this;
    }

    Polynomial<Type> &operator+=(const Polynomial<Type> &other) {
        if (data_.size() < other.data_.size()) {
            data_.resize(other.data_.size());
        }
        for (int i = 0; i < other.data_.size(); i++) {
            data_[i] += other.data_[i];
        }
        cut();
        return *this;
    }

    Polynomial<Type> operator+(const Polynomial<Type> &other) const {
        Polynomial<Type> pol_res(*this);
        pol_res += other;
        return pol_res;
    }

    Polynomial<Type> &operator-=(const Polynomial<Type> &other) {
        if (data_.size() < other.data_.size()) {
            data_.resize(other.data_.size());
        }
        for (int i = 0; i < data_.size(); i++) {
            data_[i] -= other.data_[i];
        }
        cut();
        return *this;
    }

    Polynomial<Type> operator-(const Polynomial<Type> &other) const {
        Polynomial<Type> pol_res(*this);
        pol_res -= other;
        return pol_res;
    }

    Polynomial<Type> &operator*=(const Polynomial<Type> &other) {
        *this = *this * other;
        return *this;
    }

    Polynomial<Type> operator*(const Polynomial<Type> &other) const {
        Polynomial<Type> pol_res;
        pol_res.data_.resize(data_.size() + other.data_.size() - 1);
        for (int i = 0; i < data_.size(); i++) {
            for (int j = 0; j < other.data_.size(); j++) {
                pol_res[i + j] += data_[i] * other.data_[j];
            }
        }
        return pol_res;
    }

    Polynomial<Type> &operator/=(const Polynomial<Type> &other) {
        if (data_.size() < other.data_.size()) {
            return *this;
        }
        Polynomial<Type> pol_res;
        Polynomial<Type> quotient;
        while (data_.size() >= other.data_.size()) {
            quotient.data_.resize(data_.size() - other.data_.size() + 1);
            quotient.data_.back() = data_.back() / other.data_.back();
            pol_res += quotient;
            *this -= quotient * other;
        }
        *this = pol_res;
        return *this;
    }

    Polynomial<Type> operator/(const Polynomial<Type> &other) const {
        Polynomial<Type> pol_res(*this);
        pol_res /= other;
        return pol_res;
    }

    bool operator==(const Polynomial<Type> &other) const {
        return data_ == other.data_;
    }

    Polynomial<Type> differ() const {
        Polynomial<Type> pol_res;
        pol_res.data_.resize(data_.size() - 1);
        for (int i = 0; i < pol_res.data_.size(); i++) {
            pol_res[i] = data_[i + 1] * (i + 1);
        }
        return pol_res;
    }

    Polynomial<Type> antidiffer() const {
        Polynomial<Type> pol_res;
        pol_res.data_.resize(data_.size() + 1);
        for (int i = 1; i < pol_res.data_.size(); i++) {
            pol_res[i] = data_[i - 1] / i;
        }
        return pol_res;
    }

    Type operator()(const Type x) const {
        Type res = 0;
        for (int i = 0; i < data_.size(); i++) {
            res += data_[i] * (std::pow(x, i));
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

#endif //I_HATE_CPP_POLYNOMIAL_H