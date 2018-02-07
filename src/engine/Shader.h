#ifndef _SHADER_H
#define _SHADER_H
#include <GL/glew.h>
#include <string>
#include <fstream>

#include "Texture.h"

class Shader
{
    bool compiled;
    std::string errStr;
    GLuint programID;
    static std::string getShaderLog(GLuint);
    static std::string getProgramLog(GLuint);
public:
    Shader(std::string errStr);
    Shader(GLuint programID);
    Shader();
    void bindArrayBuffer(GLuint attribLocation, GLuint bufferObject, GLenum type, GLint size, GLsizei stride);
    void use();
    void bindTexture(int target, char* uniform, Texture);
    GLint getUniformLocation(std::string);
    GLint getAttribLocation(std::string);
    GLuint getProgramID();
    bool isCompiled();
    std::string getErrorString();

    static Shader loadShaderFromFile(std::string path);

    void set(std::string, float);;
    void set(std::string, float, float);
    void set(std::string, float, float, float);
    void set(std::string, float, float, float, float);
    void set(std::string, int);
    void set(std::string, int, int);
    void set(std::string, int, int, int);
    void set(std::string, int, int, int, int);
    void set(std::string, Color);
};

#endif