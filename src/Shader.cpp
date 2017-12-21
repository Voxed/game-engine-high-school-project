#include "Shader.h"

Shader::Shader()
{
    compiled = false;
}

Shader::Shader(std::string errStr)
{
    compiled = false;
    this->errStr = errStr;
}

Shader::Shader(GLuint programID)
{
    this->programID = programID;
}

GLint Shader::getUniformLocation(std::string s)
{
    return glGetUniformLocation(programID, s.c_str());
}

GLint Shader::getAttribLocation(std::string s)
{
    return glGetAttribLocation(programID, s.c_str());
}

GLuint Shader::getProgramID()
{
    return programID;
}

void Shader::bindArrayBuffer(GLuint attribLocation, GLuint bufferObject, GLenum type, GLint size, GLsizei stride)
{
    glEnableVertexAttribArray(attribLocation);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
    glVertexAttribPointer(attribLocation, size, type, GL_FALSE, stride, NULL);
}

void Shader::use()
{
    glUseProgram(programID);
}

bool Shader::isCompiled()
{
    return compiled;
}

std::string Shader::getErrorString()
{
    return errStr;
}

Shader Shader::loadShaderFromFile(std::string path)
{
    std::string directory = "./resources/shaders/";
    std::string vertExtension = "vert";
    std::string fragExtension = "frag";
    std::string vertexFileName = directory + path + "." + vertExtension;
    std::string fragmentFileName = directory + path + "." + fragExtension;
    std::string errStr;
    std::string vertexSrc;
    std::ifstream vertexFile((vertexFileName).c_str());
    if ( vertexFile )
    {
        vertexSrc.assign( std::istreambuf_iterator<char>( vertexFile ), std::istreambuf_iterator<char>() ); 
        std::string fragmentSrc;
        std::ifstream fragmentFile((fragmentFileName).c_str());
        if ( fragmentFile )
        {
            fragmentSrc.assign( std::istreambuf_iterator<char>( fragmentFile ), std::istreambuf_iterator<char>() ); 
            
            GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
            GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);

            const GLchar* glVertexSrc = vertexSrc.c_str();
            const GLchar* glFragmentSrc = fragmentSrc.c_str();

            glShaderSource(vertexID, 1, (const GLchar**)&glVertexSrc, NULL);
            glShaderSource(fragmentID, 1, (const GLchar**)&glFragmentSrc, NULL);

            glCompileShader(vertexID);
            glCompileShader(fragmentID);

            GLint vertexCompiled = GL_FALSE;
            glGetShaderiv(vertexID, GL_COMPILE_STATUS, &vertexCompiled);
            GLint fragmentCompiled = GL_FALSE;
            glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &fragmentCompiled);
            if( vertexCompiled != GL_TRUE )
            {
                errStr = "Failed to compile " + vertexFileName + "! Log:\n" + Shader::getShaderLog(vertexID);
            }
            else if( fragmentCompiled != GL_TRUE )
            {
                errStr = "Failed to compile " + fragmentFileName + "! Log:\n" + Shader::getShaderLog(fragmentID);
            }
            else
            {
                GLuint programID = glCreateProgram();
                glAttachShader(programID, vertexID);
                glAttachShader(programID, fragmentID);

                glLinkProgram(programID);

                GLint programSuccess = GL_FALSE;
                glGetProgramiv(programID, GL_LINK_STATUS, &programSuccess);
                if( programSuccess != GL_TRUE )
                {
                    errStr = "Program link failure! Log:\n" + Shader::getProgramLog(programID);
                }
                else
                {
                    Shader shader = Shader(programID);
                    return shader;
                }
            }
        }
        else
        {
            errStr = "Can't find shader file '" + vertexFileName + "'\n";
        }
    }
    else
    {
        errStr = "Can't find shader file '" + fragmentFileName + "'\n";
    }
    return Shader(errStr);
}

std::string Shader::getShaderLog(GLuint shader)
{
    int maxLogLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLogLength);
    char infoLog[maxLogLength];
    glGetShaderInfoLog(shader, maxLogLength, 0, infoLog);
    return std::string(infoLog);
}

std::string Shader::getProgramLog(GLuint program)
{
    int maxLogLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLogLength);
    char infoLog[maxLogLength];
    glGetProgramInfoLog(program, maxLogLength, 0, infoLog);
    return std::string(infoLog);
}