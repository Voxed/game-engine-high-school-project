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
    /**
     * @brief Get the shader log
     * 
     * @param shader The shader id
     * @return std::string The shader log
     */
    static std::string getShaderLog(GLuint);
    /**
     * @brief Get the program log
     * 
     * @param program The program id
     * @return std::string The program log
     */
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
    /**
     * @brief Get the error string
     * 
     * @return std::string Error string
     */
    std::string getErrorString();
    /**
     * @brief The update event
     * 
     * @param delta The delta speed of which the program is moving (in seconds)
     */
    static Shader loadShaderFromFile(std::string path);
    /**
     * @brief Set a float in the shader
     * 
     * @param uniform The uniform name
     * @param f1 The value
     */
    void set(std::string, float);
    /**
     * @brief Set a vec2 in the shader
     * 
     * @param uniform The uniform name
     * @param f1 The first value
     * @param f2 The second value
     */
    void set(std::string, float, float);
    /**
     * @brief Set a vec3 in the shader
     * 
     * @param uniform The uniform name
     * @param f1 The first value
     * @param f2 The second value
     * @param f3 The third value
     */
    void set(std::string, float, float, float);
    /**
     * @brief Set a vec4 in the shader
     * 
     * @param uniform The uniform name
     * @param f1 The first value
     * @param f2 The second value
     * @param f3 The third value
     * @param f4 The fourth value
     */
    void set(std::string, float, float, float, float);
    /**
     * @brief Set an int in the shader
     * 
     * @param uniform The uniform name
     * @param f1 The value
     */
    void set(std::string, int);
    /**
     * @brief Set a vec2 in the shader
     * 
     * @param uniform The uniform name
     * @param f1 The first value
     * @param f2 The second value
     */
    void set(std::string, int, int);
    /**
     * @brief Set a vec3 in the shader
     * 
     * @param uniform The uniform name
     * @param f1 The first value
     * @param f2 The second value
     * @param f3 The third value
     */
    void set(std::string, int, int, int);
    /**
     * @brief Set a vec4 in the shader
     * 
     * @param uniform The uniform name
     * @param f1 The first value
     * @param f2 The second value
     * @param f3 The third value
     * @param f4 The fourth value
     */
    void set(std::string, int, int, int, int);
    /**
     * @brief Set a vec4 in the shader to a color
     * 
     * @param uniform The uniform name
     * @param c The color value
     */
    void set(std::string, Color);
};

#endif