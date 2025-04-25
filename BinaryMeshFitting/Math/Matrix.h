#pragma once

#include <array>
#include "Vector.h"

namespace BMF {
namespace Math {

template<typename T, size_t Rows, size_t Cols>
class Matrix {
public:
    std::array<std::array<T, Cols>, Rows> data;

    Matrix() {
        for (auto& row : data) {
            row.fill(T(0));
        }
        // Set diagonal to 1 for square matrices
        if constexpr (Rows == Cols) {
            for (size_t i = 0; i < Rows; ++i) {
                data[i][i] = T(1);
            }
        }
    }

    std::array<T, Cols>& operator[](size_t i) { return data[i]; }
    const std::array<T, Cols>& operator[](size_t i) const { return data[i]; }

    Matrix operator*(const Matrix<T, Cols, Rows>& other) const {
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result[i][j] = T(0);
                for (size_t k = 0; k < Cols; ++k) {
                    result[i][j] += data[i][k] * other[k][j];
                }
            }
        }
        return result;
    }

    Vector<T, Rows> operator*(const Vector<T, Cols>& vec) const {
        Vector<T, Rows> result;
        for (size_t i = 0; i < Rows; ++i) {
            result[i] = T(0);
            for (size_t j = 0; j < Cols; ++j) {
                result[i] += data[i][j] * vec[j];
            }
        }
        return result;
    }

    static Matrix identity() {
        Matrix result;
        for (size_t i = 0; i < std::min(Rows, Cols); ++i) {
            result[i][i] = T(1);
        }
        return result;
    }
};

using Mat2 = Matrix<float, 2, 2>;
using Mat3 = Matrix<float, 3, 3>;
using Mat4 = Matrix<float, 4, 4>;

} // namespace Math
} // namespace BMF 