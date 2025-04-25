#pragma once

#include <cmath>
#include <array>

namespace math {
    template<typename T>
    struct vec3 {
        T x, y, z;
        
        vec3() : x(0), y(0), z(0) {}
        vec3(T x, T y, T z) : x(x), y(y), z(z) {}
        
        vec3 operator+(const vec3& other) const {
            return vec3(x + other.x, y + other.y, z + other.z);
        }
        
        vec3 operator-(const vec3& other) const {
            return vec3(x - other.x, y - other.y, z - other.z);
        }
        
        vec3 operator*(T scalar) const {
            return vec3(x * scalar, y * scalar, z * scalar);
        }
        
        T dot(const vec3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }
        
        vec3 cross(const vec3& other) const {
            return vec3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            );
        }
        
        T length() const {
            return std::sqrt(x * x + y * y + z * z);
        }
        
        vec3 normalize() const {
            T len = length();
            if (len > 0) {
                return *this * (1.0f / len);
            }
            return *this;
        }
    };

    template<typename T>
    struct mat4 {
        std::array<T, 16> data;
        
        mat4() {
            for (int i = 0; i < 16; ++i) {
                data[i] = (i % 5 == 0) ? 1 : 0; // Identity matrix
            }
        }
        
        static mat4 perspective(T fovy, T aspect, T near, T far) {
            mat4 result;
            T tanHalfFovy = std::tan(fovy / 2);
            
            result.data[0] = 1 / (aspect * tanHalfFovy);
            result.data[5] = 1 / tanHalfFovy;
            result.data[10] = -(far + near) / (far - near);
            result.data[11] = -1;
            result.data[14] = -(2 * far * near) / (far - near);
            result.data[15] = 0;
            
            return result;
        }
        
        static mat4 lookAt(const vec3<T>& eye, const vec3<T>& center, const vec3<T>& up) {
            vec3<T> f = (center - eye).normalize();
            vec3<T> s = f.cross(up).normalize();
            vec3<T> u = s.cross(f);
            
            mat4 result;
            result.data[0] = s.x;
            result.data[1] = u.x;
            result.data[2] = -f.x;
            result.data[4] = s.y;
            result.data[5] = u.y;
            result.data[6] = -f.y;
            result.data[8] = s.z;
            result.data[9] = u.z;
            result.data[10] = -f.z;
            result.data[12] = -s.dot(eye);
            result.data[13] = -u.dot(eye);
            result.data[14] = f.dot(eye);
            
            return result;
        }
    };
    
    using vec3f = vec3<float>;
    using mat4f = mat4<float>;
} 