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

void Shader::bindTexture(int target, char* uniform, Texture texture)
{
    GLint programBak;
    glGetIntegerv(GL_CURRENT_PROGRAM, &programBak);
    bool use = (programBak != programID);

    //Generated code
    GLenum targetE = target==0 ? GL_TEXTURE0 : target==1 ? GL_TEXTURE1 : target==2 ? GL_TEXTURE2 : target==3 ? GL_TEXTURE3 : target==4 ? GL_TEXTURE4 : target==5 ? GL_TEXTURE5 : target==6 ? GL_TEXTURE6 : target==7 ? GL_TEXTURE7 : target==8 ? GL_TEXTURE8 : target==9 ? GL_TEXTURE9 : target==10 ? GL_TEXTURE10 : target==11 ? GL_TEXTURE11 : target==12 ? GL_TEXTURE12 : target==13 ? GL_TEXTURE13 : target==14 ? GL_TEXTURE14 : target==15 ? GL_TEXTURE15 : target==16 ? GL_TEXTURE16 : target==17 ? GL_TEXTURE17 : target==18 ? GL_TEXTURE18 : target==19 ? GL_TEXTURE19 : target==20 ? GL_TEXTURE20 : target==21 ? GL_TEXTURE21 : target==22 ? GL_TEXTURE22 : target==23 ? GL_TEXTURE23 : target==24 ? GL_TEXTURE24 : target==25 ? GL_TEXTURE25 : target==26 ? GL_TEXTURE26 : target==27 ? GL_TEXTURE27 : target==28 ? GL_TEXTURE28 : target==29 ? GL_TEXTURE29 : target==30 ? GL_TEXTURE30 : target==31 ? GL_TEXTURE31 : 0;

    if (use) glUseProgram(programID);
    glActiveTexture( targetE );
    glBindTexture( GL_TEXTURE_2D, texture.getTextureID() );
    glUniform1i(getUniformLocation(uniform), target);
    if (use) glUseProgram(programBak);
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
    GLint programBak;
    glGetIntegerv(GL_CURRENT_PROGRAM, &programBak);
    bool use = (programBak != programID);

    if (use) glUseProgram(programID);
    glEnableVertexAttribArray(attribLocation);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
    glVertexAttribPointer(attribLocation, size, type, GL_FALSE, stride, NULL);
    if (use) glUseProgram(programBak);
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