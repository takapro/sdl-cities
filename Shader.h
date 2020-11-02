#pragma once
#include <GL/glew.h>

class Shader {
public:
    Shader() {}
    ~Shader();

    bool Load(const char* vertName, const char* fragName);

    void SetActive();

private:
    bool CompileShader(const char* fileName, GLenum shaderType, GLuint& outShader);
    bool IsCompiled(GLuint shader);
    bool IsValidProgram();

    GLuint vertexShader;
    GLuint fragShader;
    GLuint shaderProgram;
};
