#pragma once

class VertexArray {
public:
    VertexArray() : vertexBuffer(0), indexBuffer(0), vertexArray(0) {}
    ~VertexArray();

    void Init(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices);
    void InitSquare();

    void SetActive();

    unsigned int GetNumIndices() const { return numIndices; }
    unsigned int GetNumVerts() const { return numVerts; }

private:
    unsigned int numVerts;
    unsigned int numIndices;

    unsigned int vertexBuffer;
    unsigned int indexBuffer;
    unsigned int vertexArray;
};
