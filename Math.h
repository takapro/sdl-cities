#pragma once
#include <math.h>

float deg2rad(float deg);

struct Vector2d {
    float x;
    float y;

    static Vector2d rotate2d(float rad);

    float length() const;
    Vector2d normalized() const;
};

struct Vector3d {
    float x;
    float y;
    float z;

    static Vector3d rotate3d(Vector2d vec);

    float length() const;
    Vector3d normalized() const;

    Vector3d negated() const;

    Vector3d rotated(Vector3d axis, float rad) const;
};

Vector3d operator +(const Vector3d& vec1, const Vector3d& vec2);
Vector3d operator -(const Vector3d& vec1, const Vector3d& vec2);

Vector3d operator *(float scalar, const Vector3d& vec);

float dot(const Vector3d& vec1, const Vector3d& vec2);
Vector3d cross(const Vector3d& vec1, const Vector3d& vec2);

struct Matrix4d {
    float m[16];

    static Matrix4d unit();

    static Matrix4d move(Vector3d vec);
    static Matrix4d scale(float s);
    static Matrix4d scale(Vector3d vec);

    static Matrix4d rotateX(float rad);
    static Matrix4d rotateY(float rad);
    static Matrix4d rotateZ(float rad);
};

Matrix4d operator *(const Matrix4d& mat1, const Matrix4d& mat2);
