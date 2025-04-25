#pragma once

#include "Matrix.h"
#include "Vector.h"

namespace BMF {
namespace Math {

inline Mat4 perspective(float fovy, float aspect, float zNear, float zFar) {
    Mat4 result;
    float tanHalfFovy = std::tan(fovy / 2.0f);
    
    result[0][0] = 1.0f / (aspect * tanHalfFovy);
    result[1][1] = 1.0f / tanHalfFovy;
    result[2][2] = -(zFar + zNear) / (zFar - zNear);
    result[2][3] = -1.0f;
    result[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);
    result[3][3] = 0.0f;
    
    return result;
}

inline Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
    Vec3 f = (center - eye).normalize();
    Vec3 s = f.cross(up).normalize();
    Vec3 u = s.cross(f);
    
    Mat4 result;
    result[0][0] = s[0];  result[0][1] = u[0];  result[0][2] = -f[0];  result[0][3] = 0.0f;
    result[1][0] = s[1];  result[1][1] = u[1];  result[1][2] = -f[1];  result[1][3] = 0.0f;
    result[2][0] = s[2];  result[2][1] = u[2];  result[2][2] = -f[2];  result[2][3] = 0.0f;
    result[3][0] = -s.dot(eye);
    result[3][1] = -u.dot(eye);
    result[3][2] = f.dot(eye);
    result[3][3] = 1.0f;
    
    return result;
}

inline Mat4 translate(const Mat4& m, const Vec3& v) {
    Mat4 result = m;
    result[3][0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0];
    result[3][1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1];
    result[3][2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2];
    result[3][3] = m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3];
    return result;
}

inline Mat4 rotate(const Mat4& m, float angle, const Vec3& v) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    Vec3 axis = v.normalize();
    Vec3 temp = axis * (1.0f - c);
    
    Mat4 rotate;
    rotate[0][0] = c + temp[0] * axis[0];
    rotate[0][1] = temp[0] * axis[1] + s * axis[2];
    rotate[0][2] = temp[0] * axis[2] - s * axis[1];
    
    rotate[1][0] = temp[1] * axis[0] - s * axis[2];
    rotate[1][1] = c + temp[1] * axis[1];
    rotate[1][2] = temp[1] * axis[2] + s * axis[0];
    
    rotate[2][0] = temp[2] * axis[0] + s * axis[1];
    rotate[2][1] = temp[2] * axis[1] - s * axis[0];
    rotate[2][2] = c + temp[2] * axis[2];
    
    Mat4 result;
    result[0] = m[0] * rotate[0][0] + m[1] * rotate[0][1] + m[2] * rotate[0][2];
    result[1] = m[0] * rotate[1][0] + m[1] * rotate[1][1] + m[2] * rotate[1][2];
    result[2] = m[0] * rotate[2][0] + m[1] * rotate[2][1] + m[2] * rotate[2][2];
    result[3] = m[3];
    
    return result;
}

inline Mat4 scale(const Mat4& m, const Vec3& v) {
    Mat4 result;
    result[0] = m[0] * v[0];
    result[1] = m[1] * v[1];
    result[2] = m[2] * v[2];
    result[3] = m[3];
    return result;
}

} // namespace Math
} // namespace BMF 