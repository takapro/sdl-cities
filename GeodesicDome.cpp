#include "GeodesicDome.h"
#include <math.h>

inline Vector3d calcv3d(Vector2d vec)
{
    float r = cosf(vec.y);
    return Vector3d { cosf(vec.x) * r, sinf(vec.y), sinf(vec.x) * r };
}

inline Vector2d midpoint(Vector2d a, Vector2d b)
{
    Vector3d v1 = calcv3d(a);
    Vector3d v2 = calcv3d(b);
    Vector3d v { (v1.x + v2.x) / 2, (v1.y + v2.y) / 2, (v1.z + v2.z) / 2 };
    return Vector2d { atan2f(v.z, v.x), atan2f(v.y, sqrtf(v.z * v.z + v.x * v.x)) };
}

void GeodesicDome::calc(SphericalTriangle tri, int level)
{
    if (level == 0) {
        emit(tri.a);
        emit(tri.b);
        emit(tri.c);
        return;
    }

    Vector2d ab = midpoint(tri.a, tri.b);
    Vector2d bc = midpoint(tri.b, tri.c);
    Vector2d ca = midpoint(tri.c, tri.a);
    calc(SphericalTriangle { tri.a, ab, ca }, level - 1);
    calc(SphericalTriangle { tri.b, bc, ab }, level - 1);
    calc(SphericalTriangle { tri.c, ca, bc }, level - 1);
    calc(SphericalTriangle { ab, bc, ca }, level - 1);
}

void GeodesicDome::emit(Vector2d vec)
{
    Vector3d v = calcv3d(vec);
    vertices.push_back(v.x);
    vertices.push_back(v.y);
    vertices.push_back(v.z);
    vertices.push_back((vec.y == rightAngle || vec.y == - rightAngle) ? 0.5f : vec.x / rightAngle);
    vertices.push_back((north ? 0.0f : 1.0f) - vec.y / rightAngle);
    indices.push_back(indices.size());
}

void GeodesicDome::initVertexArray(VertexArray& vertexArray)
{
    vertexArray.Init(true, vertices.data(), vertices.size(), indices.data(), indices.size());
}
