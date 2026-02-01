//
// Created by sourmnms on 1/25/26.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaders-old.h"
#include <iostream>

// shader stuff
unsigned int makeShaderProgram(const char* vertexSource, const char* fragmentSource)
{
    unsigned int vertexShader = makeShader(GL_VERTEX_SHADER, &vertexSource);
    unsigned int fragmentShader = makeShader(GL_FRAGMENT_SHADER, &fragmentSource);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkShaderCompiled(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}


unsigned int makeShader(GLenum type, auto source)
{
    unsigned int newShader = glCreateShader(type);
    glShaderSource(newShader, 1, source, NULL);
    glCompileShader(newShader);
    checkShaderCompiled(newShader);
    return newShader;
}


bool checkShaderCompiled(unsigned int &shader)
{
    int success = false;
    char infoLog[512];

    if (glIsShader(shader))
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
    else if (glIsProgram(shader))
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED" << infoLog << std::endl;
        }
    }

    return success;
}
