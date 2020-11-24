#pragma once
#include "Math.h"
#include <GL/glew.h>

class Shader {
public:
    Shader() : vertexShader(0), fragShader(0), shaderProgram(0) {}
    ~Shader();

    bool Load(const char* vertName, const char* fragName);

    void SetActive();
    void SetWorldTransform(const Matrix4d& matrix);
    void SetViewProjection(const Matrix4d& matrix);

private:
    bool CompileShader(const char* fileName, GLenum shaderType, GLuint& outShader);
    bool IsCompiled(GLuint shader);
    bool IsValidProgram();

    GLuint vertexShader;
    GLuint fragShader;
    GLuint shaderProgram;

    GLuint worldTransform;
    GLuint viewProjection;
};
