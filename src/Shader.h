#ifndef _SHADER_H
#define _SHADER_H
#include <GL/glew.h>
#include <string>
#include <fstream>

class Shader
{
    bool compiled;
    std::string errStr;
public:
    Shader(std::string errStr);
    Shader(GLuint programID);
    bool isCompiled();
    std::string getErrorString();

    static Shader loadShaderFromFile(std::string path);
    static std::string getShaderLog(GLuint);
    static std::string getProgramLog(GLuint);
};

#endif