#ifndef I_HATE_CPP_POLYNOMIAL_H
#define I_HATE_CPP_POLYNOMIAL_H

#include <initializer_list>
#include <vector>
#include <map>
#include <iterator>

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

    Type root(Type approx_root, int iterates) const{
        for(int i = 0; i < iterates; i++){
            approx_root = approx_root - (*this)(approx_root)/(*this).differ()(approx_root);
        }
        return approx_root;
    }
};

template<typename Type>
struct Monomial {
    unsigned int degree;
    Type coef;
};

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
        for (const std::pair<int, Type> &element: pol.data_) {
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

    Type operator()(const Type x) const{
        Type res = 0;
        for(const std::pair<int, Type> &mon: data_){
            res += mon.second * std::pow(x, mon.first);
        }
        return res;
    }

    Type root(Type approx_root, int iterates) const{
        for(int i = 0; i < iterates; i++){
            approx_root = approx_root - (*this)(approx_root)/(*this).differ()(approx_root);
        }
        return approx_root;
    }
};

#endif //I_HATE_CPP_POLYNOMIAL_H