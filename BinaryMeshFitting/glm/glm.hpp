#pragma once

#include <cmath>
#include <array>

namespace glm {
    template<typename T, int N>
    struct vec {
        std::array<T, N> data;
        
        vec() { data.fill(0); }
        vec(T v) { data.fill(v); }
        vec(T x, T y, T z) { data[0] = x; data[1] = y; data[2] = z; }
        
        T& operator[](int i) { return data[i]; }
        const T& operator[](int i) const { return data[i]; }
        
        T& x() { return data[0]; }
        T& y() { return data[1]; }
        T& z() { return data[2]; }
        
        const T& x() const { return data[0]; }
        const T& y() const { return data[1]; }
        const T& z() const { return data[2]; }
        
        vec operator+(const vec& other) const {
            vec result;
            for(int i = 0; i < N; ++i) {
                result[i] = data[i] + other[i];
            }
            return result;
        }
        
        vec operator-(const vec& other) const {
            vec result;
            for(int i = 0; i < N; ++i) {
                result[i] = data[i] - other[i];
            }
            return result;
        }
        
        vec operator*(T scalar) const {
            vec result;
            for(int i = 0; i < N; ++i) {
                result[i] = data[i] * scalar;
            }
            return result;
        }
        
        vec operator*(const vec& other) const {
            vec result;
            for(int i = 0; i < N; ++i) {
                result[i] = data[i] * other[i];
            }
            return result;
        }
        
        T length() const {
            T sum = 0;
            for(int i = 0; i < N; ++i) {
                sum += data[i] * data[i];
            }
            return std::sqrt(sum);
        }
        
        vec normalize() const {
            T len = length();
            if(len == 0) return *this;
            return *this * (1.0f / len);
        }
    };
    
    using vec2 = vec<float, 2>;
    using vec3 = vec<float, 3>;
    using vec4 = vec<float, 4>;
    using ivec3 = vec<int, 3>;
    
    template<typename T, int N, int M>
    struct mat {
        std::array<std::array<T, M>, N> data;
        
        mat() { 
            for(auto& row : data) row.fill(0);
            for(int i = 0; i < std::min(N, M); ++i) {
                data[i][i] = 1;
            }
        }
        
        std::array<T, M>& operator[](int i) { return data[i]; }
        const std::array<T, M>& operator[](int i) const { return data[i]; }
    };
    
    using mat4 = mat<float, 4, 4>;
    
    mat4 perspective(float fovy, float aspect, float zNear, float zFar) {
        mat4 result;
        float tanHalfFovy = std::tan(fovy / 2.0f);
        
        result[0][0] = 1.0f / (aspect * tanHalfFovy);
        result[1][1] = 1.0f / tanHalfFovy;
        result[2][2] = -(zFar + zNear) / (zFar - zNear);
        result[2][3] = -1.0f;
        result[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
        result[3][3] = 0.0f;
        
        return result;
    }
    
    mat4 lookAt(vec3 eye, vec3 center, vec3 up) {
        vec3 f = (center - eye).normalize();
        vec3 s = (f * up).normalize();
        vec3 u = s * f;
        
        mat4 result;
        result[0][0] = s[0];
        result[1][0] = s[1];
        result[2][0] = s[2];
        result[0][1] = u[0];
        result[1][1] = u[1];
        result[2][1] = u[2];
        result[0][2] = -f[0];
        result[1][2] = -f[1];
        result[2][2] = -f[2];
        result[3][0] = -s[0] * eye[0] - s[1] * eye[1] - s[2] * eye[2];
        result[3][1] = -u[0] * eye[0] - u[1] * eye[1] - u[2] * eye[2];
        result[3][2] = f[0] * eye[0] + f[1] * eye[1] + f[2] * eye[2];
        
        return result;
    }
} 