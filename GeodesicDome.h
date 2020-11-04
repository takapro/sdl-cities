#pragma once
#include "VertexArray.h"
#include <vector>

constexpr float rightAngle = static_cast<float>(M_PI / 2);

struct Vector2d {
    float x;
    float y;
};

struct Vector3d {
    float x;
    float y;
    float z;
};

struct SphericalTriangle {
    Vector2d a;
    Vector2d b;
    Vector2d c;
};

class GeodesicDome {
public:
    GeodesicDome(bool north) : north(north) {}
    void calc(SphericalTriangle tri, int level);
    void initVertexArray(VertexArray& vertexArray);

private:
    void emit(Vector2d v);

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    bool north;
};
