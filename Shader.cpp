#include "Shader.h"
#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
}

bool Shader::Load(const char* vertName, const char* fragName)
{
    if (!CompileShader(vertName, GL_VERTEX_SHADER, vertexShader) ||
        !CompileShader(fragName, GL_FRAGMENT_SHADER, fragShader)) {
        return false;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);

    worldTransform = glGetUniformLocation(shaderProgram, "uWorldTransform");
    viewProjection = glGetUniformLocation(shaderProgram, "uViewProjection");

    return IsValidProgram();
}

bool Shader::CompileShader(const char* fileName, GLenum shaderType, GLuint& outShader)
{
    std::ifstream shaderFile(fileName);
    if (!shaderFile.is_open()) {
        SDL_Log("Can't open shader file %s", fileName);
        return false;
    }

    std::stringstream sstream;
    sstream << shaderFile.rdbuf();
    std::string content = sstream.str();
    const char* contentStr = content.c_str();

    outShader = glCreateShader(shaderType);
    glShaderSource(outShader, 1, &contentStr, nullptr);
    glCompileShader(outShader);

    if (!IsCompiled(outShader)) {
        SDL_Log("Failed to compile shader %s", fileName);
        return false;
    }

    return true;
}

bool Shader::IsCompiled(GLuint shader)
{
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetShaderInfoLog(shader, 511, nullptr, buffer);
        SDL_Log("GLSL compile failed:\n%s", buffer);
        return false;
    }
    return true;
}

bool Shader::IsValidProgram()
{
    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        memset(buffer, 0, 512);
        glGetProgramInfoLog(shaderProgram, 511, nullptr, buffer);
        SDL_Log("GLSL link failed:\n%s", buffer);
        return false;
    }
    return true;
}

void Shader::SetActive()
{
    glUseProgram(shaderProgram);
}

void Shader::SetWorldTransform(const Matrix4d& matrix)
{
    glUniformMatrix4fv(worldTransform, 1, GL_FALSE, matrix.m);
}

void Shader::SetViewProjection(const Matrix4d& matrix)
{
    glUniformMatrix4fv(viewProjection, 1, GL_FALSE, matrix.m);
}
