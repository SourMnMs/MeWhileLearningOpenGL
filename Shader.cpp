//
// Created by sourmnms on 1/27/26.
//

#include "Shader.h"

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    /* ******************************************************************** */
    /*             STEP 1: retrieve vertex/fragment source code             */
    /* ******************************************************************** */
    std::string vertexCode;
    std::ifstream vertexShaderFile;

    std::string fragmentCode;
    std::ifstream fragmentShaderFile;

    // ensure ifstream objects can throw exceptions
    // I have NO IDEA what this actually does lmao
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertexShaderFile.open(vertexPath);              // open
        fragmentShaderFile.open(fragmentPath);

        std::stringstream vertexShaderStream;
        std::stringstream fragmentShaderStream;

        vertexShaderStream << vertexShaderFile.rdbuf(); // read file's buffer contents
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();                       // close
        fragmentShaderFile.close();

        vertexCode = vertexShaderStream.str();          // convert to string
        fragmentCode = fragmentShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_READ_FAILED: " << e.what() << std::endl;
    }

    // convert to c-style string
    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();


    /* ********************************************************************* */
    /*                         STEP 2: compile shader                        */
    /* ********************************************************************* */
    unsigned int vertex = makeShader(GL_VERTEX_SHADER, &vertexShaderCode);
    unsigned int fragment = makeShader(GL_FRAGMENT_SHADER, &fragmentShaderCode);

    // shader program
    programID = glCreateProgram();
    glAttachShader(programID, vertex);
    glAttachShader(programID, fragment);
    glLinkProgram(programID);
    checkCompileErrors(programID);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}


void Shader::use()
{
    glUseProgram(programID);
}


// Makes a shader of type [[GLenum]]
unsigned int Shader::makeShader(GLenum type, auto source)
{
    unsigned int newShader = glCreateShader(type);
    glShaderSource(newShader, 1, source, NULL);
    glCompileShader(newShader);
    checkCompileErrors(newShader);
    return newShader;
}

bool Shader::checkCompileErrors(unsigned int &shader)
{
    int success = false;

    constexpr int infoLogSize = 512;
    char infoLog[infoLogSize];

    if (glIsShader(shader))
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, infoLogSize, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    else if (glIsProgram(shader))
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(shader, infoLogSize, NULL, infoLog);
            std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR::NOT_SHADER_OR_SHADER_PROGRAM";
    }

    return success;
}



void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int) value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}


void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}


void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
}


void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
}


void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
}


void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
