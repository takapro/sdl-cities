#pragma once

class VertexArray {
public:
    ~VertexArray();

    void Init(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices);
    void InitSquare();

    void Render();

private:
    unsigned int numVerts;
    unsigned int numIndices;

    unsigned int vertexBuffer = 0;
    unsigned int indexBuffer = 0;
    unsigned int vertexArray = 0;
};
