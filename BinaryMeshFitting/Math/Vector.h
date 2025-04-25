#pragma once

#include <array>
#include <cmath>

namespace BMF {
namespace Math {

template<typename T, size_t N>
class Vector {
public:
    std::array<T, N> data;

    Vector() { data.fill(T(0)); }
    
    explicit Vector(T value) { data.fill(value); }
    
    Vector(T x, T y) requires (N >= 2) {
        data[0] = x;
        data[1] = y;
    }
    
    Vector(T x, T y, T z) requires (N >= 3) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }
    
    Vector(T x, T y, T z, T w) requires (N >= 4) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = w;
    }

    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }

    T& x() { return data[0]; }
    T& y() requires (N >= 2) { return data[1]; }
    T& z() requires (N >= 3) { return data[2]; }
    T& w() requires (N >= 4) { return data[3]; }

    const T& x() const { return data[0]; }
    const T& y() const requires (N >= 2) { return data[1]; }
    const T& z() const requires (N >= 3) { return data[2]; }
    const T& w() const requires (N >= 4) { return data[3]; }

    Vector operator+(const Vector& other) const {
        Vector result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] + other[i];
        }
        return result;
    }

    Vector operator-(const Vector& other) const {
        Vector result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] - other[i];
        }
        return result;
    }

    Vector operator*(T scalar) const {
        Vector result;
        for (size_t i = 0; i < N; ++i) {
            result[i] = data[i] * scalar;
        }
        return result;
    }

    T dot(const Vector& other) const {
        T result = T(0);
        for (size_t i = 0; i < N; ++i) {
            result += data[i] * other[i];
        }
        return result;
    }

    Vector cross(const Vector& other) const requires (N == 3) {
        return Vector(
            data[1] * other[2] - data[2] * other[1],
            data[2] * other[0] - data[0] * other[2],
            data[0] * other[1] - data[1] * other[0]
        );
    }

    T length() const {
        return std::sqrt(dot(*this));
    }

    Vector normalize() const {
        T len = length();
        if (len == T(0)) return *this;
        return *this * (T(1) / len);
    }
};

using Vec2 = Vector<float, 2>;
using Vec3 = Vector<float, 3>;
using Vec4 = Vector<float, 4>;
using IVec2 = Vector<int, 2>;
using IVec3 = Vector<int, 3>;
using IVec4 = Vector<int, 4>;

} // namespace Math
} // namespace BMF 