#pragma once
#include "Math.h"
#include <GL/glew.h>

class Shader {
public:
    ~Shader();

    bool Load(const char* vertName, const char* fragName);

    void SetActive();
    void SetWorldTransform(const Matrix4d& matrix);
    void SetViewProjection(const Matrix4d& matrix);

private:
    bool CompileShader(const char* fileName, GLenum shaderType, GLuint& outShader);
    bool IsCompiled(GLuint shader);
    bool IsValidProgram();

    GLuint vertexShader = 0;
    GLuint fragShader = 0;
    GLuint shaderProgram = 0;

    GLuint worldTransform;
    GLuint viewProjection;
};
