#include "GeodesicDome.h"
#include <algorithm>

constexpr float rightAngle = static_cast<float>(M_PI / 2);

GeodesicDome::GeodesicDome(bool north, int level)
{
    SphericalTriangle tri { "a", "b", "c" };
    if (north) {
        vertices[tri.a] = { 0, 0 };
        vertices[tri.b] = { rightAngle / 2, rightAngle };
        vertices[tri.c] = { rightAngle, 0 };
    } else {
        vertices[tri.a] = { 0, 0 };
        vertices[tri.b] = { rightAngle, 0 };
        vertices[tri.c] = { rightAngle / 2, - rightAngle };
    }
    Divide(tri, level);
}

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

void GeodesicDome::Divide(SphericalTriangle tri, int level)
{
    if (level == 0) {
        triangles.push_back(tri);
        return;
    }

    std::string ab = ":" + tri.a + tri.b;
    std::string bc = ":" + tri.b + tri.c;
    std::string ca = ":" + tri.c + tri.a;

    if (vertices.find(ab) == vertices.end()) {
        vertices[ab] = midpoint(vertices.at(tri.a), vertices.at(tri.b));
    }
    if (vertices.find(bc) == vertices.end()) {
        vertices[bc] = midpoint(vertices.at(tri.b), vertices.at(tri.c));
    }
    if (vertices.find(ca) == vertices.end()) {
        vertices[ca] = midpoint(vertices.at(tri.c), vertices.at(tri.a));
    }

    Divide({ tri.a, ab, ca }, level - 1);
    Divide({ tri.b, bc, ab }, level - 1);
    Divide({ tri.c, ca, bc }, level - 1);
    Divide({ ab, bc, ca }, level - 1);
}

void GeodesicDome::LoadVertexArray(VertexArray& vertexArray)
{
    float* verts = new float[vertices.size() * 5];
    unsigned int* indices = new unsigned int[triangles.size() * 3];
    std::map<std::string, unsigned int> keyIndices;

    unsigned int i = 0;
    for (const auto& [key, vec] : vertices) {
        Vector3d v = calcv3d(vec);
        verts[i * 5 + 0] = v.x;
        verts[i * 5 + 1] = v.y;
        verts[i * 5 + 2] = v.z;
        verts[i * 5 + 3] = vec.x / rightAngle;
        verts[i * 5 + 4] = (north ? 1.0f : 0.0f) - vec.y / rightAngle;
        keyIndices[key] = i++;
    }

    i = 0;
    for (const auto& tri : triangles) {
        indices[i * 3 + 0] = keyIndices.at(tri.a);
        indices[i * 3 + 1] = keyIndices.at(tri.b);
        indices[i * 3 + 2] = keyIndices.at(tri.c);
        ++i;
    }

    vertexArray.Load(verts, vertices.size(), indices, triangles.size() * 3);

    delete[] indices;
    delete[] verts;
}
