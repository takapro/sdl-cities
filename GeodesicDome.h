#pragma once
#include "Math.h"
#include "VertexArray.h"
#include <string>
#include <map>
#include <vector>

struct SphericalTriangle {
    std::string a;
    std::string b;
    std::string c;
};

class GeodesicDome {
public:
    GeodesicDome(bool north, int level);

    void LoadVertexArray(VertexArray& vertexArray, int textureSize);

private:
    void Divide(SphericalTriangle tri, int level);

    std::map<std::string, Vector2d> vertices;
    std::vector<SphericalTriangle> triangles;
    bool north;
};
