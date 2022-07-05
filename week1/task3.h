#ifndef I_HATE_CPP_TASK3_H
#define I_HATE_CPP_TASK3_H

#endif //I_HATE_CPP_TASK3_H

#include <array>
#include <vector>
#include <initializer_list>
#include <cmath>
#include <cassert>

template<typename Type, int N>
class Vector {
private:
    static_assert(N >= 0, "N must be an integer equal to or greater than 0");
    std::array<Type, N> data_;
public:
    constexpr Vector() {
        data_ = {};
    }

    constexpr Vector(const Vector<Type, N> &other) {
        for (int i = 0; i < N; i++) {
            data_[i] = other.data_[i];
        }
    }

    constexpr Vector(const std::initializer_list<Type> &list) {
        int i = 0;
        for (const auto &element: list) {
            data_[i] = element;
            i++;
        }
    }

    const Type &operator[](unsigned int i) const {
        return data_[i];
    }

    Type &operator[](unsigned int i) {
        return data_[i];
    }

    Type norm() const {
        Type res = 0;
        for (int i = 0; i < N; i++) {
            res += pow(data_[i], 2);
        }
        return sqrt(res);
    }

    Vector<Type, N> operator*=(Type num) {
        *this = (*this) * num;
        return *this;
    }

    Vector<Type, N> operator/=(Type num) {
        *this = (*this) / num;
        return *this;
    }

    Vector<Type, N> operator+=(const Vector<Type, N> &other) {
        *this = (*this) + other;
        return *this;
    }

    Vector<Type, N> operator-=(const Vector<Type, N> &other) {
        *this = (*this) - other;
        return *this;
    }

    Vector<Type, N> operator*(Type num) const {
        Vector<Type, N> v_res;
        for (int i = 0; i < N; i++) {
            v_res.data_[i] = data_[i] * num;
        }
        return v_res;
    }

    Vector<Type, N> operator/(Type num) const {
        Vector<Type, N> v_res;
        for (int i = 0; i < N; i++) {
            v_res.data_[i] = data_[i] / num;
        }
        return v_res;
    }

    Vector<Type, N> operator+(const Vector<Type, N> &other) const {
        Vector<Type, N> v_res;
        for (int i = 0; i < N; i++) {
            v_res.data_[i] = data_[i] + other.data_[i];
        }
        return v_res;
    }

    Vector<Type, N> operator-(const Vector<Type, N> &other) const {
        return (*this) + (other * (-1));
    }

    friend Vector<Type, N> operator*(Type num, const Vector<Type, N> &vec) {
        Vector<Type, N> v_res = vec * num;
        return v_res;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector<Type, N> &vec) {
        if (N == 0) {
            return out;
        }
        out << "(";
        for (int i = 0; i < vec.data_.size(); i++) {
            if (i != vec.data_.size() - 1) {
                out << vec.data_[i] << ", ";
                continue;
            }
            out << vec.data_[i] << ")" << std::endl;
        }
        return out;
    }
};

constexpr int Dynamic = -1;

template<typename Type>
class Vector<Type, Dynamic> {
private:
    std::vector<Type> data_;
    int size_;

public:
    constexpr Vector() {
        data_ = {};
        size_ = 0;
    }

    constexpr Vector(const Vector<Type, Dynamic> &other) {
        for (int i = 0; i < other.size_; i++) {
            data_.push_back(other.data_[i]);
        }
        size_ = other.size_;
    }

    constexpr Vector(const std::initializer_list<Type> &list) {
        for (const auto &element: list) {
            data_.push_back(element);
        }
        size_ = list.size();
    }

    const Type &operator[](unsigned int i) const {
        return data_[i];
    }

    Type &operator[](unsigned int i) {
        return data_[i];
    }

    Type norm() const {
        Type res = 0;
        for (int i = 0; i < size_; i++) {
            res += pow(data_[i], 2);
        }
        return sqrt(res);
    }

    Vector<Type, Dynamic> operator*=(Type num) {
        *this = (*this) * num;
        return *this;
    }

    Vector<Type, Dynamic> operator/=(Type num) {
        *this = (*this) / num;
        return *this;
    }

    Vector<Type, Dynamic> operator+=(const Vector<Type, Dynamic> &other) {
        *this = *this + other;
        return *this;
    }

    Vector<Type, Dynamic> operator-=(const Vector<Type, Dynamic> &other) {
        *this = *this + other;
        return *this;
    }

    Vector<Type, Dynamic> operator*(Type num) const {
        Vector<Type, Dynamic> v_res;
        for (int i = 0; i < size_; i++) {
            v_res.data_.push_back(data_[i] * num);
            v_res.size_++;
        }
        return v_res;
    }

    Vector<Type, Dynamic> operator/(Type num) const {
        Vector<Type, Dynamic> v_res;
        for (int i = 0; i < size_; i++) {
            v_res.data_.push_back(data_[i] / num);
            v_res.size_++;
        }
        return v_res;
    }

    Vector<Type, Dynamic> operator+(const Vector<Type, Dynamic> &other) const {
        assert(size_ == other.size_ && "Summand vectors must be the same size");
        Vector<Type, Dynamic> v_res;
        for (int i = 0; i < size_; i++) {
            v_res.data_.push_back(data_[i] + other.data_[i]);
            v_res.size_++;
        }
        return v_res;
    }

    Vector<Type, Dynamic> operator-(const Vector<Type, Dynamic> &other) const {
        return (*this) + (other * (-1));
    }

    friend Vector<Type, Dynamic> operator*(Type num, const Vector<Type, Dynamic> &vec) {
        return vec * num;
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector<Type, Dynamic> &vec) {
        if (vec.size_ == 0) {
            return out;
        }
        out << "(";
        for (int i = 0; i < vec.size_; i++) {
            if (i != vec.data_.size() - 1) {
                out << vec.data_[i] << ", ";
                continue;
            }
            out << vec.data_[i] << ")" << std::endl;
        }
        return out;
    }
};