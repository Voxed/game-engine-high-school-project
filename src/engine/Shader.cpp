#include "Shader.h"

/**
 * @brief Initialize an empty shader object
 * 
 */
Shader::Shader()
{
    compiled = false;
}

/**
 * @brief Initialize a shader object with an error
 * 
 * @param errStr The error string
 */
Shader::Shader(std::string errStr)
{
    compiled = false;
    this->errStr = errStr;
}

/**
 * @brief Initialize a shader from a program id
 * 
 * @param programID The program id
 */
Shader::Shader(GLuint programID)
{
    this->programID = programID;
}

/**
 * @brief Bind a texture to the shader
 * 
 * @param target The texture id to bind to
 * @param uniform The uniform to bind it to
 * @param texture The texture to be bound
 */
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

/**
 * @brief Get a uniform location
 * 
 * @param s The name of the unifrom
 * @return GLint The location of a uniform
 */
GLint Shader::getUniformLocation(std::string s)
{
    return glGetUniformLocation(programID, s.c_str());
}

/**
 * @brief Get an attribute location
 * 
 * @param s The name of the attribute
 * @return GLint The location of the attribute
 */
GLint Shader::getAttribLocation(std::string s)
{
    return glGetAttribLocation(programID, s.c_str());
}

/**
 * @brief Get the program id
 * 
 * @return GLuint The program id
 */
GLuint Shader::getProgramID()
{
    return programID;
}

/**
 * @brief Bind an array buffer
 * 
 * @param attribLocation The attribute location
 * @param bufferObject The buffer object
 * @param type The type of the data
 * @param size The size of the object
 * @param stride The stride
 */
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

/**
 * @brief Bind the shader
 * 
 */
void Shader::use()
{
    glUseProgram(programID);
}

/**
 * @brief Returns if the shader compiled correctly
 * 
 * @return true Shader compiled
 * @return false Shader did not compile, check for errors
 */
bool Shader::isCompiled()
{
    return compiled;
}

/**
 * @brief Get the error string
 * 
 * @return std::string Error string
 */
std::string Shader::getErrorString()
{
    return errStr;
}

/**
 * @brief Load a shader from a file
 * 
 * @param name The name of the shader
 * @return Shader The shader object
 */
Shader Shader::loadShaderFromFile(std::string name)
{
    std::string directory = "./resources/shaders/";
    std::string vertExtension = "vert";
    std::string fragExtension = "frag";
    std::string vertexFileName = directory + name + "." + vertExtension;
    std::string fragmentFileName = directory + name + "." + fragExtension;
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

/**
 * @brief Get the shader log
 * 
 * @param shader The shader id
 * @return std::string The shader log
 */
std::string Shader::getShaderLog(GLuint shader)
{
    int maxLogLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLogLength);
    char infoLog[maxLogLength];
    glGetShaderInfoLog(shader, maxLogLength, 0, infoLog);
    return std::string(infoLog);
}

/**
 * @brief Get the program log
 * 
 * @param program The program id
 * @return std::string The program log
 */
std::string Shader::getProgramLog(GLuint program)
{
    int maxLogLength;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLogLength);
    char infoLog[maxLogLength];
    glGetProgramInfoLog(program, maxLogLength, 0, infoLog);
    return std::string(infoLog);
}

/**
 * @brief Set a float in the shader
 * 
 * @param uniform The uniform name
 * @param f1 The value
 */
void Shader::set(std::string uniform, float f1)
{
    this->use();
    glUniform1f(this->getUniformLocation(uniform), f1);
}

/**
 * @brief Set a vec2 in the shader
 * 
 * @param uniform The uniform name
 * @param f1 The first value
 * @param f2 The second value
 */
void Shader::set(std::string uniform, float f1, float f2)
{
    this->use();
    glUniform2f(this->getUniformLocation(uniform), f1, f2);
}

/**
 * @brief Set a vec3 in the shader
 * 
 * @param uniform The uniform name
 * @param f1 The first value
 * @param f2 The second value
 * @param f3 The third value
 */
void Shader::set(std::string uniform, float f1, float f2, float f3)
{
    this->use();
    glUniform3f(this->getUniformLocation(uniform), f1, f2, f3);
}

/**
 * @brief Set a vec4 in the shader
 * 
 * @param uniform The uniform name
 * @param f1 The first value
 * @param f2 The second value
 * @param f3 The third value
 * @param f4 The fourth value
 */
void Shader::set(std::string uniform, float f1, float f2, float f3, float f4)
{
    this->use();
    glUniform4f(this->getUniformLocation(uniform), f1, f2, f3, f4);
}

/**
 * @brief Set an int in the shader
 * 
 * @param uniform The uniform name
 * @param f1 The value
 */
void Shader::set(std::string uniform, int f1)
{
    this->use();
    glUniform1i(this->getUniformLocation(uniform), f1);
}

/**
 * @brief Set a vec2 in the shader
 * 
 * @param uniform The uniform name
 * @param f1 The first value
 * @param f2 The second value
 */
void Shader::set(std::string uniform, int f1, int f2)
{
    this->use();
    glUniform2i(this->getUniformLocation(uniform), f1, f2);
}

/**
 * @brief Set a vec3 in the shader
 * 
 * @param uniform The uniform name
 * @param f1 The first value
 * @param f2 The second value
 * @param f3 The third value
 */
void Shader::set(std::string uniform, int f1, int f2, int f3)
{
    this->use();
    glUniform3i(this->getUniformLocation(uniform), f1, f2, f3);
}

/**
 * @brief Set a vec4 in the shader
 * 
 * @param uniform The uniform name
 * @param f1 The first value
 * @param f2 The second value
 * @param f3 The third value
 * @param f4 The fourth value
 */
void Shader::set(std::string uniform, int f1, int f2, int f3, int f4)
{
    this->use();
    glUniform4i(this->getUniformLocation(uniform), f1, f2, f3, f4);
}

/**
 * @brief Set a vec4 in the shader to a color
 * 
 * @param uniform The uniform name
 * @param c The color value
 */
void Shader::set(std::string uniform, Color c)
{
    this->set(uniform, c.r, c.g, c.b, c.a);
}