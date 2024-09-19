//
// Created by Jun Wei Moo on 19/9/24.
//

#ifndef MATH_H
#define MATH_H

#include <cmath>

struct Vector3 {
    float x, y, z;

    Vector3(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {}

    Vector3 Normalize() const {
        float length = sqrtf(x*x + y*y + z*z);
        return Vector3(x / length, y / length, z / length);
    }

    Vector3 Cross(const Vector3& other) const {
        return Vector3(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    float Dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }
};

struct Matrix4x4 {
    float m[4][4];

    Matrix4x4(
        float m00=1, float m01=0, float m02=0, float m03=0,
        float m10=0, float m11=1, float m12=0, float m13=0,
        float m20=0, float m21=0, float m22=1, float m23=0,
        float m30=0, float m31=0, float m32=0, float m33=1
    ) {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
        m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
    }

    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result;
        for(int row=0; row<4; ++row){
            for(int col=0; col<4; ++col){
                result.m[row][col] =
                    m[row][0] * other.m[0][col] +
                    m[row][1] * other.m[1][col] +
                    m[row][2] * other.m[2][col] +
                    m[row][3] * other.m[3][col];
            }
        }
        return result;
    }
};

#endif
