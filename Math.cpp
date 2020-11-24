#include "Math.h"

float deg2rad(float deg) {
    return deg * static_cast<float>(M_PI) / 180.0f;
}

Vector2d Vector2d::rotate(float rad) {
    return { cosf(rad), sinf(rad) };
}

float Vector2d::length() const {
    return sqrtf(x * x + y * y);
}

Vector2d Vector2d::normalized() const {
    float len = length();
    return { x / len, y / len };
}

float Vector3d::length() const {
    return sqrtf(x * x + y * y + z * z);
}

Vector3d Vector3d::normalized() const {
    float len = length();
    return { x / len, y / len, z / len };
}

Vector3d Vector3d::negated() const {
    return { - x, - y, - z };
}

Vector3d operator -(const Vector3d& vec1, const Vector3d& vec2) {
    return { vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z };
}

Vector3d cross(const Vector3d& vec1, const Vector3d& vec2) {
    return {
        vec1.y * vec2.z - vec1.z * vec2.y,
        vec1.z * vec2.x - vec1.x * vec2.z,
        vec1.x * vec2.y - vec1.y * vec2.x,
    };
}

Matrix4d Matrix4d::unit() {
    return {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };
}

Matrix4d Matrix4d::move(Vector3d vec) {
    auto [x, y, z] = vec;
    return {
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1,
    };
}

Matrix4d Matrix4d::scale(float s) {
    return {
        s, 0, 0, 0,
        0, s, 0, 0,
        0, 0, s, 0,
        0, 0, 0, 1,
    };
}

Matrix4d Matrix4d::scale(Vector3d vec) {
    auto [x, y, z] = vec;
    return {
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1,
    };
}

Matrix4d Matrix4d::rotateX(float rad) {
    auto [c, s] = Vector2d::rotate(rad);
    return {
        1, 0, 0, 0,
        0, c, -s, 0,
        0, s, c, 0,
        0, 0, 0, 1,
    };
}

Matrix4d Matrix4d::rotateY(float rad) {
    auto [c, s] = Vector2d::rotate(rad);
    return {
        c, 0, -s, 0,
        0, 1, 0, 0,
        s, 0, c, 0,
        0, 0, 0, 1,
    };
}

Matrix4d Matrix4d::rotateZ(float rad) {
    auto [c, s] = Vector2d::rotate(rad);
    return {
        c, -s, 0, 0,
        s, c, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };
}

Matrix4d operator *(const Matrix4d& mat1, const Matrix4d& mat2) {
    Matrix4d matrix;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix.m[i * 4 + j] =
                mat1.m[i * 4 + 0] * mat2.m[j + 0] +
                mat1.m[i * 4 + 1] * mat2.m[j + 4] +
                mat1.m[i * 4 + 2] * mat2.m[j + 8] +
                mat1.m[i * 4 + 3] * mat2.m[j + 12];
        }
    }
    return matrix;
}
